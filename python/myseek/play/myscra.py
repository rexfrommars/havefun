#!/usr/bin/env python

import scrapy


class SeekSpider(scrapy.Spider):
    name = 'seek-spider'
    start_urls = [
        'http://seek.co.nz',
    ]

    def parse(self, response):
        pass


def test_ss():
    pass

def main():
    pass


if __name__ == '__main__':
    main()
