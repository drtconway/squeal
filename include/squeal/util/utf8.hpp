#ifndef SQUEAL_UTIL_UTF8_HPP
#define SQUEAL_UTIL_UTF8_HPP

#include <stdexcept>
#include <string>
#include <vector>

namespace squeal
{
    namespace util
    {
        namespace utf8
        {
            struct encoder
            {
                encoder(std::string& p_dest)
                    : m_dest(p_dest)
                {
                }

                encoder& push_back(char32_t p_ch)
                {
                    if (p_ch <= 0x7F)
                    {
                        m_dest.push_back(p_ch);
                    }
                    else if (p_ch <= 0x7FF)
                    {
                        uint8_t c1 = 0x80 | (p_ch & 0x3F);
                        p_ch >>= 6;
                        uint8_t c0 = 0xC0 | (p_ch & 0x1F);
                        m_dest.push_back(c0);
                        m_dest.push_back(c1);
                    }
                    else if (p_ch <= 0xFFFF)
                    {
                        uint8_t c2 = 0x80 | (p_ch & 0x3F);
                        p_ch >>= 6;
                        uint8_t c1 = 0x80 | (p_ch & 0x3F);
                        p_ch >>= 6;
                        uint8_t c0 = 0xE0 | (p_ch & 0xF);
                        m_dest.push_back(c0);
                        m_dest.push_back(c1);
                        m_dest.push_back(c2);
                    }
                    else if (p_ch <= 0x10FFF)
                    {
                        uint8_t c3 = 0x80 | (p_ch & 0x3F);
                        p_ch >>= 6;
                        uint8_t c2 = 0x80 | (p_ch & 0x3F);
                        p_ch >>= 6;
                        uint8_t c1 = 0x80 | (p_ch & 0x3F);
                        p_ch >>= 6;
                        uint8_t c0 = 0xF0 | (p_ch & 0x7);
                        m_dest.push_back(c0);
                        m_dest.push_back(c1);
                        m_dest.push_back(c2);
                        m_dest.push_back(c3);
                    }
                    else
                    {
                        throw std::runtime_error("code point out of range");
                    }
                    return *this;
                }

            private:
                std::string& m_dest;
            };

            std::string to_utf8(const std::u32string& p_u32str)
            {
                std::string res;
                encoder enc(res);
                for (auto itr = p_u32str.begin(); itr != p_u32str.end(); ++itr)
                {
                    enc.push_back(*itr);
                }
                return res;
            }

            struct decoder
            {
                class const_iterator
                {
                public:
                    const_iterator(std::string::const_iterator p_itr)
                        : m_itr(p_itr), m_cur(0), m_len(0)
                    {}

                    bool operator==(const const_iterator& p_other) const
                    {
                        return m_itr == p_other.m_itr;
                    }

                    bool operator!=(const const_iterator& p_other) const
                    {
                        return m_itr != p_other.m_itr;
                    }

                    char32_t operator*()
                    {
                        if (m_len == 0)
                        {
                            load_next();
                        }
                        return m_cur;
                    }

                    const_iterator& operator++()
                    {
                        if (m_len == 0)
                        {
                            load_next();
                        }
                        m_itr += m_len;
                        m_cur = 0;
                        m_len = 0;
                        return *this;
                    }

                    const_iterator operator++(int)
                    {
                        const_iterator other(m_itr);
                        ++(*this);
                        return other;
                    }

                private:
                    void load_next()
                    {
                        auto itr = m_itr;
                        char32_t c0 = static_cast<uint8_t>(*itr++);
                        if ((c0 & 0x80) == 0)
                        {
                            // done!
                        }
                        else if ((c0 & 0xE0) == 0xC0)
                        {
                            char32_t c1 = static_cast<uint8_t>(*itr++);
                            require((c1 & 0xC0) == 0x80);
                            c0 &= 0x0F;
                            c0 <<= 6;
                            c0 |= ( c1 & 0x3F );
                        }
                        else if ((c0 & 0xF0) == 0xE0)
                        {
                            char32_t c1 = static_cast<uint8_t>(*itr++);
                            char32_t c2 = static_cast<uint8_t>(*itr++);
                            require((c1 & 0xC0) == 0x80 && (c2 & 0xC0) == 0x80);
                            c0 &= 0x0F;
                            c0 <<= 6;
                            c0 |= ( c1 & 0x3F );
                            c0 <<= 6;
                            c0 |= ( c2 & 0x3F );
                        }
                        else if ((c0 & 0xF8) == 0xF0)
                        {
                            char32_t c1 = static_cast<uint8_t>(*itr++);
                            char32_t c2 = static_cast<uint8_t>(*itr++);
                            char32_t c3 = static_cast<uint8_t>(*itr++);
                            require((c1 & 0xC0) == 0x80 && (c2 & 0xC0) == 0x80 && (c3 & 0xC0) == 0x80);
                            c0 &= 0x0F;
                            c0 <<= 6;
                            c0 |= ( c1 & 0x3F );
                            c0 <<= 6;
                            c0 |= ( c2 & 0x3F );
                            c0 <<= 6;
                            c0 |= ( c3 & 0x3F );
                        }
                        else
                        {
                            require(false);
                        }
                        m_cur = c0;
                        m_len = itr - m_itr;
                    }

                    void require(bool p_ok)
                    {
                        if (p_ok)
                        {
                            return;
                        }
                        throw std::runtime_error("malformed utf8");
                    }

                    std::string::const_iterator m_itr;
                    char32_t m_cur;
                    int m_len;
                };

                decoder(const std::string& p_str)
                    : m_begin(p_str.begin()), m_end(p_str.end())
                {
                }

                decoder(std::string::const_iterator p_begin, std::string::const_iterator p_end)
                    : m_begin(p_begin), m_end(p_end)
                {
                }

                const_iterator begin() const
                {
                    return const_iterator(m_begin);
                }

                const_iterator end() const
                {
                    return const_iterator(m_end);
                }

                static void decode(const std::string& p_str, std::vector<char32_t>& p_chs)
                {
                    decoder dec(p_str);
                    for (auto itr = dec.begin(); itr != dec.end(); ++itr)
                    {
                        p_chs.push_back(*itr);
                    }
                }

            private:
                std::string::const_iterator m_begin;
                std::string::const_iterator m_end;
            };

            std::u32string from_utf8(const std::string& p_utf8str)
            {
                std::u32string res;
                decoder dec(p_utf8str);
                for (auto itr = dec.begin(); itr != dec.end(); ++itr)
                {
                    res.push_back(*itr);
                }
                return res;
            }
        }
        // namespace utf8
    }
    // namespace util
}
// namespace squeal

#endif // SQUEAL_UTIL_UTF8_HPP
