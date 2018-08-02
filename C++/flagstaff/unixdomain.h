#ifndef _FLAGSTAFF_UNIX_DOMAIN_H
#define _FLAGSTAFF_UNIX_DOMAIN_H

namespace flagstaff
{

class StreamConn : public Epollee
{};

class StreamListener
{};

class SeqPacketConn : public Epollee
{};

class SeqPacketListener
{};

}

#endif // _FLAGSTAFF_UNIX_DOMAIN_H
