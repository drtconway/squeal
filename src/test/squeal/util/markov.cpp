#include "squeal/util/markov.hpp"

#define BOOST_TEST_MODULE squeal markov
#include <boost/test/unit_test.hpp>

#include <deque>
#include <iostream>
#include "squeal/util/utf8.hpp"

namespace // anonymous
{
    const std::string utf8En =
        "it was the best of times, "
        "It was the worst of times, "
        "it was the age of wisdom, "
        "it was the age of foolishness, "
        "it was the epoch of belief, "
        "it was the epoch of incredulity, "
        "it was the season of Light, "
        "it was the season of Darkness, "
        "it was the spring of hope, "
        "it was the winter of despair, "
        "we had everything before us, "
        "we had nothing before us, "
        "we were all going direct to Heaven, "
        "we were all going direct the other way-- "
        "in short, the period was so far like the present period, that some of "
        "its noisiest authorities insisted on its being received, for good or for "
        "evil, in the superlative degree of comparison only. "
        " "
        "There were a king with a large jaw and a queen with a plain face, on the "
        "throne of England; there were a king with a large jaw and a queen with "
        "a fair face, on the throne of France. In both countries it was clearer "
        "than crystal to the lords of the State preserves of loaves and fishes, "
        "that things in general were settled for ever. "
        " "
        "It was the year of Our Lord one thousand seven hundred and seventy-five. "
        "Spiritual revelations were conceded to England at that favoured period, "
        "as at this. Mrs. Southcott had recently attained her five-and-twentieth "
        "blessed birthday, of whom a prophetic private in the Life Guards had "
        "heralded the sublime appearance by announcing that arrangements were "
        "made for the swallowing up of London and Westminster. Even the Cock-lane "
        "ghost had been laid only a round dozen of years, after rapping out its "
        "messages, as the spirits of this very year last past (supernaturally "
        "deficient in originality) rapped out theirs. Mere messages in the "
        "earthly order of events had lately come to the English Crown and People, "
        "from a congress of British subjects in America: which, strange "
        "to relate, have proved more important to the human race than any "
        "communications yet received through any of the chickens of the Cock-lane "
        "brood. "
        " "
        "France, less favoured on the whole as to matters spiritual than her "
        "sister of the shield and trident, rolled with exceeding smoothness down "
        "hill, making paper money and spending it. Under the guidance of her "
        "Christian pastors, she entertained herself, besides, with such humane "
        "achievements as sentencing a youth to have his hands cut off, his tongue "
        "torn out with pincers, and his body burned alive, because he had not "
        "kneeled down in the rain to do honour to a dirty procession of monks "
        "which passed within his view, at a distance of some fifty or sixty "
        "yards. It is likely enough that, rooted in the woods of France and "
        "Norway, there were growing trees, when that sufferer was put to death, "
        "already marked by the Woodman, Fate, to come down and be sawn into "
        "boards, to make a certain movable framework with a sack and a knife in "
        "it, terrible in history. It is likely enough that in the rough outhouses "
        "of some tillers of the heavy lands adjacent to Paris, there were "
        "sheltered from the weather that very day, rude carts, bespattered with "
        "rustic mire, snuffed about by pigs, and roosted in by poultry, which "
        "the Farmer, Death, had already set apart to be his tumbrils of "
        "the Revolution. But that Woodman and that Farmer, though they work "
        "unceasingly, work silently, and no one heard them as they went about "
        "with muffled tread: the rather, forasmuch as to entertain any suspicion "
        "that they were awake, was to be atheistical and traitorous. "
        " "
        "In England, there was scarcely an amount of order and protection to "
        "justify much national boasting. Daring burglaries by armed men, and "
        "highway robberies, took place in the capital itself every night; "
        "families were publicly cautioned not to go out of town without removing "
        "their furniture to upholsterers' warehouses for security; the highwayman "
        "in the dark was a City tradesman in the light, and, being recognised and "
        "challenged by his fellow-tradesman whom he stopped in his character of "
        "“the Captain,” gallantly shot him through the head and rode away; the "
        "mail was waylaid by seven robbers, and the guard shot three dead, and "
        "then got shot dead himself by the other four, “in consequence of the "
        "failure of his ammunition:” after which the mail was robbed in peace; "
        "that magnificent potentate, the Lord Mayor of London, was made to stand "
        "and deliver on Turnham Green, by one highwayman, who despoiled the "
        "illustrious creature in sight of all his retinue; prisoners in London "
        "gaols fought battles with their turnkeys, and the majesty of the law "
        "fired blunderbusses in among them, loaded with rounds of shot and ball; "
        "thieves snipped off diamond crosses from the necks of noble lords at "
        "Court drawing-rooms; musketeers went into St. Giles's, to search "
        "for contraband goods, and the mob fired on the musketeers, and the "
        "musketeers fired on the mob, and nobody thought any of these occurrences "
        "much out of the common way. In the midst of them, the hangman, ever busy "
        "and ever worse than useless, was in constant requisition; now, stringing "
        "up long rows of miscellaneous criminals; now, hanging a housebreaker on "
        "Saturday who had been taken on Tuesday; now, burning people in the "
        "hand at Newgate by the dozen, and now burning pamphlets at the door of "
        "Westminster Hall; to-day, taking the life of an atrocious murderer, "
        "and to-morrow of a wretched pilferer who had robbed a farmer's boy of "
        "sixpence. "
        "All these things, and a thousand like them, came to pass in and close "
        "upon the dear old year one thousand seven hundred and seventy-five. "
        "Environed by them, while the Woodman and the Farmer worked unheeded, "
        "those two of the large jaws, and those other two of the plain and the "
        "fair faces, trod with stir enough, and carried their divine rights "
        "with a high hand. Thus did the year one thousand seven hundred "
        "and seventy-five conduct their Greatnesses, and myriads of small "
        "creatures--the creatures of this chronicle among the rest--along the "
        "roads that lay before them. ";

        std::string str(const std::u32string& p_str)
        {
            return squeal::util::utf8::to_utf8(p_str);
        }

        std::string str(const char32_t& p_ch)
        {
            std::u32string s;
            s.push_back(p_ch);
            return str(s);
        }

        std::u32string u32(const std::string& p_utf8)
        {
            return squeal::util::utf8::from_utf8(p_utf8);
        }

        template <size_t N>
        size_t count(const squeal::util::markov<N>& p_model, const std::string& p_ctxt, char32_t p_ch)
        {
            std::u32string ctxt = squeal::util::utf8::from_utf8(p_ctxt);
            auto itr = p_model.txs.find(ctxt);
            if (itr == p_model.txs.end())
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
}
// namespace anonymous

BOOST_AUTO_TEST_CASE( cons0 )
{
    std::u32string u32En = squeal::util::utf8::from_utf8(utf8En);

    static constexpr size_t N = 1;
    squeal::util::markov<N> M;
    M.insert(u32En);

    BOOST_CHECK_EQUAL(count(M, "C", 'h'), 1);
    BOOST_CHECK_EQUAL(count(M, "e", 's'), 54);
    BOOST_CHECK_EQUAL(count(M, "g", '.'), 1);
    BOOST_CHECK_EQUAL(count(M, "h", 'o'), 28);
    BOOST_CHECK_EQUAL(count(M, "s", 'o'), 8);
    BOOST_CHECK_EQUAL(count(M, "t", 'a'), 15);
    BOOST_CHECK_EQUAL(count(M, "u", 'i'), 2);
    BOOST_CHECK_EQUAL(count(M, "w", 'a'), 32);
    BOOST_CHECK_EQUAL(count(M, "w", 'r'), 1);
    BOOST_CHECK_EQUAL(count(M, "y", 's'), 2);
}

BOOST_AUTO_TEST_CASE( cons1 )
{
    std::u32string u32En = squeal::util::utf8::from_utf8(utf8En);

    static constexpr size_t N = 2;
    squeal::util::markov<N> M;
    M.insert(u32En);

    BOOST_CHECK_EQUAL(count(M, " t", 'h'), 133);
    BOOST_CHECK_EQUAL(count(M, "th", 'e'), 105);
    BOOST_CHECK_EQUAL(count(M, " o", 'f'), 57);
    BOOST_CHECK_EQUAL(count(M, "an", 'd'), 55);
    BOOST_CHECK_EQUAL(count(M, " a", 'n'), 48);
    BOOST_CHECK_EQUAL(count(M, "in", 'g'), 30);
    BOOST_CHECK_EQUAL(count(M, " t", 'o'), 29);

#if 0
    for (auto itr = M.txs.begin(); itr != M.txs.end(); ++itr)
    {
        for (auto jtr = itr->second.begin(); jtr != itr->second.end(); ++jtr)
        {
            std::cout << str(itr->first) << '\t' << str(jtr->first) << '\t' << jtr->second << std::endl;
        }
    }
#endif
}

BOOST_AUTO_TEST_CASE( contains0 )
{
    std::u32string u32En = squeal::util::utf8::from_utf8(utf8En);

    static constexpr size_t N = 1;
    squeal::util::markov<N> M;
    
    BOOST_CHECK_EQUAL(M.contains(u32("attained")), false);
    M.insert(u32En);
    BOOST_CHECK_EQUAL(M.contains(u32("attained")), true);
    BOOST_CHECK_EQUAL(M.contains(u32("fig")), true);

}

BOOST_AUTO_TEST_CASE( contains1 )
{
    std::u32string u32En = squeal::util::utf8::from_utf8(utf8En);

    static constexpr size_t N = 2;
    squeal::util::markov<N> M;
    
    BOOST_CHECK_EQUAL(M.contains(u32("attained")), false);
    M.insert(u32En);
    BOOST_CHECK_EQUAL(M.contains(u32("attained")), true);
    BOOST_CHECK_EQUAL(M.contains(u32("fig")), false);

}

BOOST_AUTO_TEST_CASE( next0 )
{
    std::u32string u32En = squeal::util::utf8::from_utf8(utf8En);

    static constexpr size_t N = 2;
    squeal::util::markov<N> M;
    
    M.insert(u32En);

    std::mt19937 rng(17);
    std::uniform_real_distribution<double> unif;

    squeal::util::markov<N>::context ctxt = u32("fi");
    char32_t ch = 0;
    M.next([&]() mutable { return unif(rng); }, ctxt, ch);
    BOOST_CHECK_EQUAL(str(ch), "c");
}

BOOST_AUTO_TEST_CASE( nextp0 )
{
    std::u32string u32En = squeal::util::utf8::from_utf8(utf8En);

    static constexpr size_t N = 2;
    squeal::util::markov<N> M;
    
    M.insert(u32En);

    std::mt19937 rng(17);
    std::uniform_real_distribution<double> unif;

    squeal::util::markov<N>::context ctxt = u32("fi");
    char32_t ch = 0;
    M.next([&]() mutable { return unif(rng); },
           [](char32_t p_ch) { return 'a' <= p_ch && p_ch <= 'z'; },
           ctxt, ch);
    BOOST_CHECK_EQUAL(str(ch), "c");
}

BOOST_AUTO_TEST_CASE( step0 )
{
    std::u32string u32En = squeal::util::utf8::from_utf8(utf8En);

    static constexpr size_t N = 1;
    squeal::util::markov<N> M;
    
    M.insert(u32En);

    squeal::util::markov<N>::context ctxt = u32("f");
    {
        std::mt19937 rng(17);
        std::uniform_real_distribution<double> unif;

        std::u32string res;
        bool r = M.step([&]() mutable { return unif(rng); }, ctxt, 5, res);
        BOOST_CHECK_EQUAL(r, true);
        BOOST_CHECK_EQUAL(str(res), " trom");
    }
    {
        std::mt19937 rng(20);
        std::uniform_real_distribution<double> unif;

        std::u32string res;
        bool r = M.step([&]() mutable { return unif(rng); }, ctxt, 5, res);
        BOOST_CHECK_EQUAL(r, true);
        BOOST_CHECK_EQUAL(str(res), "owoop");
    }

#if 0
    int n = 10;
    int j = 17;
    while (n > 0)
    {
        while (true)
        {
            ++j;
            std::mt19937 rng(j);
            std::uniform_real_distribution<double> unif;

            std::u32string res;
            bool r = M.step([&]() mutable { return unif(rng); }, ctxt, 5, res);
            if (r)
            {
                std::cout << j << '\t' << str(res) << std::endl;
                break;
            }
        }
        --n;
    }
#endif
}

BOOST_AUTO_TEST_CASE( stepp0 )
{
    std::u32string u32En = squeal::util::utf8::from_utf8(utf8En);

    static constexpr size_t N = 1;
    squeal::util::markov<N> M;
    
    M.insert(u32En);

    squeal::util::markov<N>::context ctxt = u32("f");
    {
        std::mt19937 rng(20);
        std::uniform_real_distribution<double> unif;

        std::u32string res;
        bool r = M.step([&]() mutable { return unif(rng); },
                        [](char32_t p_ch) { return 'a' <= p_ch && p_ch <= 'z'; },
                        ctxt, 5, res);
        BOOST_CHECK_EQUAL(r, true);
        BOOST_CHECK_EQUAL(str(res), "rturm");
    }
    {
        std::mt19937 rng(21);
        std::uniform_real_distribution<double> unif;

        std::u32string res;
        bool r = M.step([&]() mutable { return unif(rng); },
                        [](char32_t p_ch) { return 'a' <= p_ch && p_ch <= 'z'; },
                        ctxt, 5, res);
        BOOST_CHECK_EQUAL(r, true);
        BOOST_CHECK_EQUAL(str(res), "orawi");
    }
#if 0
    int n = 10;
    int j = 17;
    while (n > 0)
    {
        while (true)
        {
            ++j;
            std::mt19937 rng(j);
            std::uniform_real_distribution<double> unif;

            std::u32string res;
            bool r = M.step([&]() mutable { return unif(rng); },
                            [](char32_t p_ch) { return 'a' <= p_ch && p_ch <= 'z'; },
                            ctxt, 5, res);
            if (r)
            {
                std::cout << j << '\t' << str(res) << std::endl;
                break;
            }
        }
        --n;
    }
#endif
}
