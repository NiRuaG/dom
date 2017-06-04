#include "parser.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace dominion{ namespace parser {
    decltype(dominion::parser::counts_) dominion::parser::counts_{};

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
        auto expect = [&linestream](verb_tokens const& v, std::string const& e) {
            std::stringstream ex(e);
            std::string fromline, fromex;
            while (
                ex         >> fromex   && 
                linestream >> fromline &&  /// !destructive to linestream
                fromex == fromline)
            {
                // std::cout << fromline << " " << fromex << std::endl;
            }

            auto& vstr = verb_tokens_map.right.at(v);
            if (ex.eof() && !linestream.bad() && fromex == fromline)
                ++counts_[vstr + " " + e];
            else
            {
                std::cerr << "\b! \"" << vstr << "\" but not \"" << e << "\", found instead: \"" << fromline << "\"";
                std::cin.get();
                //throw?
            }
        };
        switch (ret.verb)
        {
        case verb_tokens::Buy: {
            expect(verb_tokens::Buy  , "and gains");
        }break;
        case verb_tokens::React: {
            expect(verb_tokens::React, "with"     );
        }break;
        case verb_tokens::Look: {
            expect(verb_tokens::Look , "at"       );
        }break;
        case verb_tokens::Start: {
            expect(verb_tokens::Start, "with"     );
        }break;

        default:
            ;
        }//switch verb


        if (ret.verb == verb_tokens::Shuffle)
            return ret; //end of line assumed ".. shuffles their deck"
        
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
        while (istr >> str) 
        {
            if (str == "and") // "and" continues the collection
                continue;

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
            } 
#ifdef _DEBUG
            else {
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
            i = (unsigned short)std::stoi(str);
        } catch (...) {
            std::cout << "\b! caught exception from stoi on string: " << str << std::endl;
            std::cin.get();
            i = 0;
        }
        return i;
    }
}} // namespace dominion::parser