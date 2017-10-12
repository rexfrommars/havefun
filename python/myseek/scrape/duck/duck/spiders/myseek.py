# -*- coding: utf-8 -*-

from twisted.internet import reactor

import scrapy
from scrapy.utils.project import get_project_settings
from scrapy.crawler import CrawlerRunner
from scrapy.utils.log import configure_logging

import re
import datetime
from urlparse import urlparse, parse_qs
import urllib


class SeekURLBuilder(object):

    SALARY_MAX = 999999
    SALARY_LIST = [0, 30000, 40000, 50000, 60000, 70000, 80000, 90000,  # 90000 is not in the original Seek list
                   100000, 120000, 150000, 200000, SALARY_MAX]

    DATE_RANGE_MAX = 999
    DATE_RANGE_LIST = [1, 3, 7, 14, 31, DATE_RANGE_MAX]

    def __init__(self):
        self._keywords = []
        self._salary_min = 60000
        self._salary_max = 999999
        self._date_range = 31

    def set_keywords(self, *keywords):
        self._keywords = [re.sub('\s+', '-', kw.strip()) for kw in keywords]

    def set_salary(self, salary_min, salary_max):
        if not salary_min < salary_max:
            raise ValueError('salary_min should less than salary_max')

        if salary_min not in self.SALARY_LIST:
            raise ValueError('salary_min not in pre-defined list')

        if salary_max not in self.SALARY_LIST:
            raise ValueError('salary_max not in pre-defined list')

        self._salary_min, self._salary_max = salary_min, salary_max

    def set_date_range(self, date_range):
        self._date_range = date_range

    def build_0(self):
        keywords = '+'.join([urllib.quote_plus(kw) for kw in self._keywords])
        path = '%(keywords)s-jobs-in-information-communication-technology/in-%(region)s/full-time?' \
               'daterange=%(date-range)s&isareaunspecified=false&salaryrange=%(s-min)s-%(s-max)s&salarytype=annual'

        params = {
            'keywords': keywords,
            'date-range': self._date_range,
            'region': 'All-Auckland',
            's-min': self._salary_min,
            's-max': self._salary_max,
        }

        return 'https://www.seek.co.nz/' + path % params

    def build_1(self):
        # Normally, an URL built in this function will be redirected (301) to the corresponding URL produced by build_0.
        # However, the URL for the keyword '"C++"' will not.
        keywords = ' '.join(self._keywords)

        # postfix = urllib.urlencode({
        #     'isareaunspecified': 'false',
        #     'salaryrange': '%s-%s' % (self._salary_min, self._salary_max),
        #     'salarytype': 'annual',
        # })
        # region = 'All-Auckland'
        # return 'https://www.seek.co.nz/' + infix + '/in-%s/full-time?' % region + postfix

        # path = '%(prefix)s/in-%(region)s/full-time?isareaunspecified=false' \
        #        '&salaryrange=%(s-min)s-%(s-max)s&salarytype=annual'

        path = 'jobs-in-information-communication-technology/in-%(region)s/full-time?' \
               'daterange=%(date-range)s&isareaunspecified=false' \
               '&keywords=%(keywords)s&salaryrange=%(s-min)s-%(s-max)s&salarytype=annual'

        params = {
            'keywords': urllib.quote_plus(keywords),
            'date-range': self._date_range,
            'region': 'All-Auckland',
            's-min': self._salary_min,
            's-max': self._salary_max,
        }

        return 'https://www.seek.co.nz/' + path % params

    def build_2(self):
        # https://jobsearch-api.cloud.seek.com.au/search?
        #   siteKey=NZ-Main&
        #   userqueryid=9203d7ce277ac498686cf0a44a46c542-2507141&
        #   userid=002e49a1-09f2-4d6a-b20a-d91c78549498&
        #   usersessionid=002e49a1-09f2-4d6a-b20a-d91c78549498&
        #   eventCaptureSessionId=ab5861be-7af1-451b-9e02-e8b6b1b251ec&
        #   where=All%20New%20Zealand&
        #   page=1&
        #   keywords=C%2B%2B&
        #   classification=6281&
        #   sourcesystem=houston
        pass

    build = build_1


class MyseekSpider(scrapy.Spider):

    _ENABLE_PROFILE = True

    _ENABLE_DETAILS = True
    _ONE_JOB = False
    _NEXT_PAGE = True

    _ENABLE_SALARY_RANGE = True

    _KEYWRODS_SET = [
        ['Python'],
        ['"C++"'],  # 'C++' won't work, with a 404 response is always returned.
        ['AWS'],
    ]

    @classmethod
    def append_keywords(cls, *keywords):
        cls._KEYWRODS_SET.append(keywords)

    name = 'myseek'
    allowed_domains = ['seek.co.nz']
    # start_urls = [
    #     'https://www.seek.co.nz/Python-jobs-in-information-communication-technology/in-All-Auckland/full-time?' \
    #     'isareaunspecified=false&salaryrange=70000-80000&salarytype=annual'
    # ]

    def start_requests(self):
        url_builder = SeekURLBuilder()
        url_builder.set_salary(60000, SeekURLBuilder.SALARY_MAX)

        salary_list = [60000, 70000, 80000, 90000, 100000, 120000, 150000]

        for keywords in self._KEYWRODS_SET:
            url_builder.set_keywords(*keywords)
            if self._ENABLE_DETAILS or self._ENABLE_PROFILE:
                url_builder.set_salary(60000, SeekURLBuilder.SALARY_MAX)
                request = scrapy.Request(url=url_builder.build(), callback=self.parse)
                request.meta['KEYWORDS'] = keywords
                yield request

            if self._ENABLE_SALARY_RANGE:
                for pair in zip(salary_list[:-1], salary_list[1:]):
                    url_builder.set_salary(pair[0], pair[1])
                    salary_range_request = scrapy.Request(url=url_builder.build(), callback=self.parse_salary_range)
                    salary_range_request.meta['KEYWORDS'] = keywords
                    salary_range_request.meta['SALARY_RANGE'] = pair
                    salary_range_request.meta['PAGE'] = 1

                    yield salary_range_request

    def _data_automation(self, obj, html_tag, data_tag):
        key = '%s[data-automation=%s]::text' % (html_tag, data_tag)
        return ''.join(obj.css(key).extract())

    def _data_automation_span(self, obj, html_tag, data_tag):
        key = '%s[data-automation=%s] span::text' % (html_tag, data_tag)
        return ''.join(obj.css(key).extract())

    def parse_salary_range(self, response):
        keywords = response.meta['KEYWORDS']
        salary_range = response.meta['SALARY_RANGE']
        page = response.meta['PAGE']
        self.log('parse_salary_range: %s (%d) on %s' % (str(keywords), page, str(salary_range)))
        job_id_list = [job.xpath('@data-job-id').extract()[0] for job in response.css('article')]
        yield {
            'category': 'salary-range',
            'keywords': keywords,
            'salary_range': salary_range,
            'page': page,
            'job_id_list': job_id_list,
        }

        next_page = (response.css('a[data-automation=page-next]') + [None])[0]
        if next_page is not None:
            next_url = response.urljoin(next_page.xpath('@href').extract_first())
            request = scrapy.Request(next_url, callback=self.parse_salary_range)
            request.meta['KEYWORDS'] = keywords
            request.meta['SALARY_RANGE'] = salary_range
            request.meta['PAGE'] = page + 1
            yield request

    def parse(self, response):
        self.log(response.url)

        keywords = response.meta['KEYWORDS']

        if self._ENABLE_PROFILE:
            job_count = response.css('strong[data-automation=totalJobsCount]::text').extract_first()
            page_count = len(response.css('a[data-automation^=page-]'))
            if page_count is 0:
                page_count = 1

            yield {
                'category':     'profile',
                'keywords':     keywords,
                'job-count':    job_count,
                'page-count':   page_count,
            }

        if not self._ENABLE_DETAILS:
            return

        for job in response.css('article'):

            detail_url = job.css('a[data-automation=jobTitle]').xpath('@href').extract_first()
            short_url = detail_url.split('?')[0]
            url_args = parse_qs(urlparse(detail_url).query)
            item_type = url_args['type']

            outlines = []
            for li in job.css('ul li'):
                outlines.append(''.join(li.css('span::text').extract()))

            info = {
                'category':     'job-detail',
                'keywords':     keywords,

                'id':           job.xpath('@data-job-id').extract()[0],

                'label':        ''.join(job.xpath('@aria-label').extract()),
                'title':        ''.join(job.css('a[data-automation=jobTitle] span::text').extract()),
                'advertiser':   self._data_automation(job, 'span', 'jobAdvertiser'),

                'location':     self._data_automation(job, 'a', 'jobLocation'),
                'area':         self._data_automation(job, 'a', 'jobArea'),
                'subClass':     self._data_automation(job, 'a', 'jobSubClassification'),

                'short-desc':   ''.join(job.css('span[data-automation=jobShortDescription] span span::text').extract()),

                'outlines':     outlines,

                'detail_url':   detail_url,
                'short_url':    short_url,
                'item_type':    item_type,
                'is_promoted':  'promoted' in item_type,
            }

            request = response.follow(short_url, callback=self.parse_detail)

            request.meta['INFO'] = info

            yield request

            if self._ONE_JOB:
                break

        if self._NEXT_PAGE and not self._ONE_JOB:
            next_page = response.css('a[data-automation=page-next]')[0]
            if next_page is not None:
                next_url = response.urljoin(next_page.xpath('@href').extract_first())
                request = scrapy.Request(next_url, callback=self.parse)
                request.meta['KEYWORDS'] = keywords
                yield request
                # yield response.follow(next_page)

    def parse_detail(self, response):
        info = response.meta['INFO']

        detail_date = ''.join(response.css('dd[data-automation=job-detail-date]')[0].css('span::text').extract())
        work_type = ''.join(response.css('dd[data-automation=job-detail-work-type]')[0].css('span::text').extract())
        detail_text = response.css('div.templatetext').extract_first()

        info['detail-date'] = detail_date
        info['detail-work-type'] = work_type
        info['detail-text'] = detail_text

        yield info


def run():
    settings = get_project_settings()
    today = datetime.date.today()
    uri_prefix = 'STORAGE/%d-%02d' % (today.year, today.month)
    settings.set('FEED_FORMAT', 'jsonlines')
    settings.set('FEED_URI', uri_prefix + '/%(name)s.%(time)s.jl')

    configure_logging()

    runner = CrawlerRunner(settings)
    runner.crawl(MyseekSpider)

    d = runner.join()
    d.addBoth(lambda _: reactor.stop())

    reactor.run()


if __name__ == '__main__':
    run()

