#include "squeal/util/markov.hpp"

#define BOOST_TEST_MODULE squeal markov
#include <boost/test/unit_test.hpp>

#include <deque>
#include <iostream>
#include <unicode/uchar.h>
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

    std::string utf8Hi =
        u8"यूनान में देवताओं की पूजा के साथ जो नृत्य प्रारंभ"
        u8"हुआ वही वहाँ का अभिनयकला का प्रथम रूप था जिसमें"
        u8"नृत्य के द्वारा कथा के भाव की अभिव्यक्ति की जाती"
        u8"थी। यूनान में प्रारंभ में धार्मिक वेदी के चारों ओर जाए"
        u8"नाटकीय नृत्य होते थे उनमें सभी लोग समान रूप से भाग लेते"
        u8"थे, किंतु पीछे चलकर समवेत गायकों में से कुछ चुने हुए"
        u8"समर्थ अभिनेता ही मुख्य भूमिकाओं के लिए चुन लिए"
        u8"जाते थे जाए एक का ही नहीं, कई की भूमिकाओं का अभिनय करते"
        u8"थे क्योंकि मुखौटा पहनने की रीति के कारण यह संभव हो"
        u8"गया था। मुखौटे के प्रयोग के कारण वहाँ वाचिक अभिनय"
        u8"तो बहुत समुन्नत हुआ किंतु मुखमुद्राओं से अभिनय करने"
        u8"की रीति पल्लवित न हो सकी।"
        u8""
        u8"इटलीवासियों में अभिनय की रुचि बड़ी स्वाभाविक है।"
        u8"नाटक लिखे जाने से बहुत पहले से ही वहाँ यह साधारण"
        u8"प्रवृत्ति रही है कि किसी दल को जहाँ कोई विषय दिया गया कि"
        u8"वह झट उसका अभिनय प्रस्तुत कर देता था। संगीत, नृत्य और"
        u8"दृश्य के इस प्रेम ने वहाँ के राजनीतिक और धार्मिक संघर्ष"
        u8"में भी अभिनयकला को जीवित रखने में बड़ी सहायता दी है।"
        u8""
        u8"यूरोप में अभिनय कला को सबसे अधिक महत्व दिया शेक्सपियर"
        u8"ने। उसने स्वयं मानव स्वभाव के सभी चरित्रों का चित्रण"
        u8"किया है। उसने हैमलेट के संवाद में श्रेष्ठ अभिनय के"
        u8"मूल तत्वों का समावेश करते हुए बताया है कि अभिनय में"
        u8"वाणी और शरीर के अंगों का प्रयोग स्वाभाविक रूप से"
        u8"करना चाहिए, अतिरंजित रूप से नहीं।"
        u8""
        u8"१८वीं शताब्दी में ही यूरोप में अभिनय के संबंध"
        u8"में विभिन्न सिद्धांतों और प्रणालियों का प्रादुर्भाव"
        u8"हुआ। फ्रांसीसी विश्वकोशकार देनी दिदरो ने उदात्तवादी"
        u8"(क्लासिकल) फ्रांसीसी नाटक और उसकी रूढ़ अभिनय पद्धति से"
        u8"ऊबकर वास्तविक जीवन के नाटक का सिद्धांत प्रतिपादित"
        u8"किया और बताया कि नाटक को फ्रांस के बुर्जुवा"
        u8"(मध्यवर्गीय) जीवन की वास्तविक प्रतिच्छाया बनना"
        u8"चाहिए। उसने अभिनेता को यह सुझाया कि प्रयोग के समय"
        u8"अपने पर ध्यान देना चाहिए, अपनी वाणी सुननी चाहिए और"
        u8"अपने आवेगों की स्मृतियाँ ही प्रस्तुत करनी चाहिए।"
        u8"किंतु 'मास्को स्टेज ऐंड इंपीरियल थिएटर' के भूतपूर्व"
        u8"प्रयोक्ता और कलासंचालक थियोदोर कौमिसारजेवस्की ने"
        u8"इस सिद्धांत का खंडन करते हुए लिखा था:"
        u8""
        u8"अब यह सिद्ध हो चुका है कि यदि अभिनेता अपने अभिनय पर"
        u8"सावधानी से ध्यान रखता रहे तो वह न दर्शकों को प्रभावित"
        u8"कर सकता है और न रंगमंच पर किसी भी प्रकार की रचानात्मक"
        u8"सृष्टि कर सकता है, क्योंकि उसे अपने आंतरिक स्वात्म"
        u8"पर जो प्रतिबिंब प्रस्तुत करते हैं उनपर एकाग्र होने के"
        u8"बदले वह अपने बाह्य स्वात्म पर एकाग्र हो जाता है जिससे"
        u8"वह इतना अधिक आत्मचेतन हो जाता है कि उसकी अपनी"
        u8"कल्पना शक्ति नष्ट हो जाती है। अत:, श्रेष्ठतर उपाय यह"
        u8"है कि वह कल्पना के आश्रय पर अभिनय करे, नवनिर्माण"
        u8"करे, नयापन लाए और केवल अपने जीवन के अनुभवों का"
        u8"अनुकरण या प्रतिरूपण न करे। जब कोई अभिनेता किसी"
        u8"भूमिका का अभिनय करते हुए अपनी स्वयं की उत्पादित"
        u8"कल्पना के विश्व में विचरण करने लगता है उस समय उसे न तो"
        u8"अपने ऊपर ध्यान देना चाहिए, न नियंत्रण रखना चाहिए और न तो"
        u8"वह ऐसा कर ही सकता है, क्योंकि अभिनेता की अपनी भावना"
        u8"से उद्भूत और उसकी आज्ञा के अनुसार काम करनेवाली"
        u8"कल्पना अभिनय के समय उसके आवेग और अभिनय को नियंत्रित"
        u8"करती, पथ दिखलाती और संचालन करती है। २०वीं शताब्दी"
        u8"में अनेक नाट्यविद्यालयों, नाट्यसंस्थाओं और रंगशालाओं"
        u8"ने अभिनय के संबंध में अनेक नए और स्पष्ट सिद्धांत"
        u8"प्रतिपादित किए। मार्क्स रीनहार्ट ने जर्मनी"
        u8"में और फ़िर्मी गेमिए ने पेरिस में उस प्रकृतिवादी"
        u8"नाट्यपद्धति का प्रचलन किया जिसका प्रतिपादन फ्रांस में"
        u8"आंदे आंत्वाँ ने और जर्मनी में क्रोनेग ने किया था और"
        u8"जिसका विकास बर्लिन में ओटोब्राह्म ने और मास्को"
        u8"में स्तानिस्लवस्की ने किया। इन प्रयोक्ताओं ने"
        u8"बीच-बीच में प्रकृतिवादी अभिनय में या तो रीतिवादी"
        u8"(फोर्मलिस्ट्स) लोगों के विचारों का सन्निवेश किया"
        u8"या सन्‌ १९१० के पश्चात्‌ क्रोमिसारजेवस्की ने"
        u8"अभिनय के संश्लेषणात्मक सिद्धांतों का जो"
        u8"प्रवर्त्तन किया था उनका भी थोड़ा बहुत समावेश किया;"
        u8"किंतु अधिकांश ्फ्रांसीसी अभिनेता १८वीं शताब्दी"
        u8"की प्राचीन रोमांसवादी (रोमांटिक) पद्धति का"
        u8"अर्धोदात्त (सूडो-क्लासिकल) अभिनयपद्धति का ही प्रयोग"
        u8"करते रहे।"
        u8""
        u8"सन्‌ १९१० के पश्चात्‌ जितने अभिनयसिद्धांत प्रसिद्ध"
        u8"हुए उनमें सर्वप्रसिद्ध मास्कों आर्ट थिएटर के"
        u8"प्रयोक्ता स्तानिसलवस्की की प्रणाली है जिसका सिद्धांत"
        u8"यह है कि कोई भी अभिनेता रंगमंच पर तभी स्वाभाविक"
        u8"और सच्चा हो सकता है जब वह उन आवेगों का प्रदर्शन"
        u8"करे जिनका उसने अपने जीवन में अनुभव किया हो। अभिनय"
        u8"में यह आंतरिक प्रकृतिवाद स्तानिसलवस्की की कोई नई"
        u8"सूझी नहीं थी क्योंकि कुछ फ्रांसीसी नाट्यज्ञों ने"
        u8"१८वीं शताब्दी में इन्हीं विचारों के आधार पर अपनी"
        u8"अभिनय पद्धतियाँ प्रवर्तित की थीं। स्तानिसलवस्की"
        u8"के अनुसार वे ही अभिनेता प्रेम के दृश्य का प्रदर्शन"
        u8"भली-भाँति कर सकते हैं जो वास्तविक जीवन में प्रेम कर"
        u8"रहे हों।"
        u8""
        u8"स्तानसिलवस्की के सिद्धांत के विरुद्ध प्रतीकवादियों"
        u8"(सिंबोलिस्ट्स), रीतिवादियों (फ़ार्मालिस्ट्स) और"
        u8"अभिव्यंजनावादियों (एक्स्प्रेशनिस्ट्स) ने नई"
        u8"रीति चलाई जिसमें सत्यता और जीवनतुल्यता का पूर्ण"
        u8"बहिष्कार करके कहा गया कि अभिनय जितना ही कम, वास्तविक"
        u8"और कम जीवनतुल्य होगा उतना ही अच्छा होगा। अभिनेता को"
        u8"निश्चित चरित्रनिर्माण करने का प्रयत्न करना चाहिए। उसे"
        u8"गूढ़ विचारों का रूढ़ रीति से अपनी वाणी, अपनी चेष्टा और"
        u8"मुद्राओं द्वारा प्रस्तुत करना चाहिए और वह अभिनय रूढ़,"
        u8"जीवन-साम्य-हीन, चित्रमय और कठपुतली--नृत्य--शैली में"
        u8"प्रस्तुत करना चाहिए।"
        u8""
        u8"रूढ़िवादी लोग आगे चलकर मेयरहोल्द, तायरोफ़ और अरविन"
        u8"पिस्काटर के नेतृत्व में अभिनय में इतनी उछल-कूद,"
        u8"नटविद्या और लयगति का प्रयोग करने लगे कि रंगमंच"
        u8"पर उनका अभिनय ऐसा प्रतीत होने लगा मानों कोई सरकस"
        u8"हो रहा हो जिसमें उछल-कूद, शरीर का कलात्मक संतुलन और"
        u8"इसी प्रकार की गतियों की प्रधानता हो। यह अभिनय ही"
        u8"घनवादी (क्यूबिस्टिक) अभिनय कहलाने लगा। इन लयवादियों"
        u8"में से मेयरहोल्द तो आगे चलकर कुछ प्रकृतिवादी"
        u8"हो गया किंतु लियोपोल्ड जेस्सवर, निकोलसऐवरेनोव"
        u8"आदि अभिव्यंजनावादी, या यों कहिए कि अतिरंजित अभिनयवादी"
        u8"लोग कुछ तो रूढ़िवादियों की प्रणालियों का अनुसरण करते"
        u8"रहे और कुछ मनोवैज्ञानिक प्रकृतिवादी पद्धति का।";

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

    template <size_t N>
    size_t count(const squeal::util::markov<N>& p_model, const std::string& p_ctxt, const std::string& p_ch)
    {
        std::u32string chStr = u32(p_ch);
        BOOST_REQUIRE_EQUAL(chStr.size(), 1);
        char32_t ch = chStr[0];

        return count(p_model, p_ctxt, ch);
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

BOOST_AUTO_TEST_CASE( cons2 )
{
    std::u32string u32Hi = squeal::util::utf8::from_utf8(utf8Hi);

    static constexpr size_t N = 2;
    squeal::util::markov<N> M;
    M.insert(u32Hi);


    BOOST_CHECK_EQUAL(count(M, u8"अप", u8"न"), 15);
    BOOST_CHECK_EQUAL(count(M, u8"कर", u8"न"), 10);
    BOOST_CHECK_EQUAL(count(M, u8"उस", u8"क"), 5);

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

BOOST_AUTO_TEST_CASE( stepp1 )
{
    std::u32string u32Hi = squeal::util::utf8::from_utf8(utf8Hi);

    static constexpr size_t N = 1;
    squeal::util::markov<N> M;
    
    M.insert(u32Hi);

    squeal::util::markov<N>::context ctxt = u32(u8"न");
#if 1
    {
        std::mt19937 rng(22);
        std::uniform_real_distribution<double> unif;

        std::u32string res = ctxt;
        bool r = M.step([&]() mutable { return unif(rng); },
                        [](char32_t p_ch) { return u_hasBinaryProperty(p_ch, UCHAR_ALPHABETIC); },
                        ctxt, 5, res);
        BOOST_CHECK_EQUAL(r, true);
        BOOST_CHECK_EQUAL(str(res), u8"नेपरीव");
    }
    {
        std::mt19937 rng(23);
        std::uniform_real_distribution<double> unif;

        std::u32string res = ctxt;
        bool r = M.step([&]() mutable { return unif(rng); },
                        [](char32_t p_ch) { return u_hasBinaryProperty(p_ch, UCHAR_ALPHABETIC); },
                        ctxt, 5, res);
        BOOST_CHECK_EQUAL(r, true);
        BOOST_CHECK_EQUAL(str(res), u8"नुकेता");
    }
#endif
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

            std::u32string res = ctxt;
            bool r = M.step([&]() mutable { return unif(rng); },
                            [](char32_t p_ch) { return u_hasBinaryProperty(p_ch, UCHAR_ALPHABETIC) && !u_hasBinaryProperty(p_ch, UCHAR_DIACRITIC); },
                            ctxt, 5, res);
            if (r)
            {
                std::cout << j << '\t' << res[0] << '\t' << str(res) << std::endl;
                break;
            }
        }
        --n;
    }
#endif
}
