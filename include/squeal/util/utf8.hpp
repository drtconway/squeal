#ifndef SQUEAL_UTIL_UTF8_HPP
#define SQUEAL_UTIL_UTF8_HPP

#include <stdexcept>

namespace squeal
{
    namespace util
    {
        namespace utf8
        {
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

            private:
                std::string::const_iterator m_begin;
                std::string::const_iterator m_end;
            };
        }
        // namespace utf8
    }
    // namespace util
}
// namespace squeal

#endif // SQUEAL_UTIL_UTF8_HPP
