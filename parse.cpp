#include <sstream>
#include "parser.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace dominion{ namespace parser {
    
    struct_turnline
        parse_turnline(std::string& str) {

        decltype(parse_turnline(str)) ret;

#ifdef _DEBUG
        std::cout << "[" << str << "]" << std::endl;
#endif
        std::stringstream linestream(str);

        std::string verb;
        linestream >> ret.playerID >> verb;
        // next token should be a (set of) verb(s)
        try {
            ret.verb = parse_verb(verb);
        } catch (...) {
            std::cout << "\b! caught parse_verb exception";
            std::cin.get();
        }
        // special verb cases
        switch (ret.verb)
        {
        case verb_tokens::Buy: {
            std::string t1, t2;
            linestream >> t1 >> t2; /// !this is destructive
            if (t1 == "and" && t2 == "gains")
            {
                ++counts_["buys and gains"];
            }
            else
            {
                std::cerr << "\b! BUYS, but not \"and gains\"";
                std::cin.get();
            }
        }break;

        case verb_tokens::React: {
            std::string t;
            linestream >> t; ///! destructive
            if (t == "with")
                ++counts_["reacts with"];
            else
            {
                std::cerr << "\b! REACTS, but not \"with\"";
                std::cin.get();
            }
        }break;

        case verb_tokens::Look: {
            std::string t;
            linestream >> t; ///! destructive
            if (t == "at")
                ++counts_["looks at"];
            else
            {
                std::cerr << "\b! LOOKS, but not \"at\"";
                std::cin.get();
            }
        }break;
        case verb_tokens::Starts: {
            std::string t;
            linestream >> t; /// destructive
            if (t == "with")
                ++counts_["starts with"];
            else
            {
                std::cerr << "\b! STARTS, but not \"with\"";
                std::cin.get();
            }
        }break;

        default:
            ;
        }//switch verb

        if (ret.verb == verb_tokens::Shuffle)
            return ret; //end of line is ".. shuffles their deck"
        
        // rest of line is set of cards
        try {
            ret.cards = parse_cards(linestream);
        } catch (...) {
            std::cout << "\b! caught parse_cards exception";
            std::cin.get();
        }

        return ret;
    }

    verb_tokens
        parse_verb(std::string& str) {
        
        auto verb_find = verb_tokens_map.left.find(str);
        if (verb_find != verb_tokens_map.left.end())
        {   
            ++counts_[verb_find->first];
            return verb_find->second;
        }

#ifdef _DEBUG
        std::cerr << "couldnt find verb for: [" << str << "]";
        std::cin.get();
#endif
        throw;
    }

    std::vector<pair_card_num>
        parse_cards(std::istream& istr) {
        
        decltype(parse_cards(istr)) ret{};

        std::string str;
        while (istr >> str && str != "and") // "and" continues to proceed
        {
            //1. number part of pair
            auto num = parse_card_num(str);

            //2. card part of pair
            std::string str_card;
            istr >> str_card;
            // ignore ',' as final character
            if (!str_card.empty() && str_card.back() == ',')
                str_card.pop_back();
            // singular-ize
            auto sing_find = singular.find(str_card);
            if (sing_find != singular.end())
                str_card = sing_find->second;
            // get card token
            auto card_find = card_tokens_map.left.find(str_card);
            if (card_find != card_tokens_map.left.end()) {
                ++counts_[card_find->first];
                //append the <num,card> pair to return
                ret.emplace_back(num, card_find->second);
            } else {
#ifdef _DEBUG
                std::cerr << "\b! couldnt find card: [" << str_card << "]";
                std::cin.get();
                throw;
#endif
            }
        }

        return ret;
    }

    unsigned short
        parse_card_num(std::string& str)
    {
        if (str == "a" || str == "an") {
            return 1;
        }
        //else
        unsigned short i;
        try {
            i = stoi(str);
        } catch (...) {
            std::cout << "\b! caught exception from stoi on string: " << str << std::endl;
            std::cin.get();
            i = 0;
        }
        return i;
    }
}} // namespace dominion::parser