#ifndef SQUEAL_UTIL_MARKOV_HPP
#define SQUEAL_UTIL_MARKOV_HPP

#include <deque>
#include <functional>
#include <map>
#include <random>
#include <string>

namespace squeal
{
    namespace util
    {
        template <size_t N = 1>
        struct markov
        {
            using context = std::u32string;
            using transitions = std::map<context, std::map<char32_t, size_t>>;

            markov() {}

            void insert(const std::u32string& p_txt)
            {
                if (p_txt.size() <= N)
                {
                    return;
                }
                std::deque<char32_t> q(p_txt.begin(), p_txt.begin() + N);
                for (auto itr = p_txt.begin() + N; itr != p_txt.end(); ++itr)
                {
                    std::u32string ctxt = std::u32string(q.begin(), q.end());
                    char32_t ch = *itr;
                    insert(ctxt, ch);
                    q.pop_front();
                    q.push_back(ch);
                }
            }

            void insert(const context& p_ctxt, char32_t p_chr)
            {
                txs[p_ctxt][p_chr] += 1;
            }

            bool contains(const std::u32string& p_txt)
            {
                if (p_txt.size() <= N)
                {
                    return false;
                }
                std::deque<char32_t> q(p_txt.begin(), p_txt.begin() + N);
                for (auto itr = p_txt.begin() + N; itr != p_txt.end(); ++itr)
                {
                    std::u32string ctxt = std::u32string(q.begin(), q.end());
                    char32_t ch = *itr;

                    if (count(ctxt, ch) == 0)
                    {
                        return false;
                    }

                    q.pop_front();
                    q.push_back(ch);
                }
                return true;
            }

            size_t count(const context& p_ctxt, const char32_t& p_ch) const
            {
                auto itr = txs.find(p_ctxt);
                if (itr == txs.end())
                {
                    return 0;
                }
                auto jtr = itr->second.find(p_ch);
                if (jtr == itr->second.end())
                {
                    return 0;
                }
                return jtr->second;
            }

            template <typename Rng>
            bool step(Rng p_rng, const context& p_ctxt, size_t p_steps, std::u32string& p_res) const
            {
                context ctxt = p_ctxt;
                for (size_t i = 0; i < p_steps; ++i)
                {
                    char32_t ch = 0;
                    if (!next(p_rng, ctxt, ch))
                    {
                        return false;
                    }
                    p_res.push_back(ch);
                    shift(ctxt, ch);
                }
                return true;
            }

            template <typename Rng, typename X>
            bool step(Rng p_rng, X p_pred, const context& p_ctxt, size_t p_steps, std::u32string& p_res) const
            {
                static_assert(std::is_convertible<X, std::function<bool(char32_t)>>::value);

                context ctxt = p_ctxt;
                for (size_t i = 0; i < p_steps; ++i)
                {
                    char32_t ch = 0;
                    if (!next(p_rng, p_pred, ctxt, ch))
                    {
                        return false;
                    }
                    p_res.push_back(ch);
                    shift(ctxt, ch);
                }
                return true;
            }

            template <typename Rng>
            bool next(Rng p_rng, const context& p_ctxt, char32_t& p_next) const
            {
                auto itr = txs.find(p_ctxt);
                if (itr == txs.end())
                {
                    return false;
                }
                const std::map<char32_t, size_t>& st = itr->second;
                double t = 0;
                for (auto jtr = st.begin(); jtr != st.end(); ++jtr)
                {
                    t += jtr->second;
                }
                double u = p_rng() * t;
                for (auto jtr = st.begin(); jtr != st.end(); ++jtr)
                {
                    if (u < jtr->second)
                    {
                        p_next = jtr->first;
                        return true;
                    }
                    u -= jtr->second;
                }
                return false;
            }

            template <typename Rng, typename X>
            bool next(Rng p_rng, X p_pred, const context& p_ctxt, char32_t& p_next) const
            {
                static_assert(std::is_convertible<X, std::function<bool(char32_t)>>::value);

                auto itr = txs.find(p_ctxt);
                if (itr == txs.end())
                {
                    return false;
                }
                const std::map<char32_t, size_t>& st = itr->second;
                double t = 0;
                for (auto jtr = st.begin(); jtr != st.end(); ++jtr)
                {
                    if (!p_pred(jtr->first))
                    {
                        continue;
                    }
                    t += jtr->second;
                }
                if (t == 0)
                {
                    return false;
                }
                double u = p_rng() * t;
                for (auto jtr = st.begin(); jtr != st.end(); ++jtr)
                {
                    if (!p_pred(jtr->first))
                    {
                        continue;
                    }
                    if (u < jtr->second)
                    {
                        p_next = jtr->first;
                        return true;
                    }
                    u -= jtr->second;
                }
                return false;
            }

            static void shift(context& p_ctxt, char32_t p_ch)
            {
                for (size_t i = 1; i < N; ++i)
                {
                    p_ctxt[i-1] = p_ctxt[i];
                }
                p_ctxt[N-1] = p_ch;
            }

            transitions txs;
        };
    }
    // namespace util
}
// namespace squeal

#endif // SQUEAL_UTIL_MARKOV_HPP
