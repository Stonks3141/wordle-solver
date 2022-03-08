#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

std::string find_color(std::string guess, std::string answer)
{
    auto color = std::string("00000");
    auto letters = std::map<char, int>{}; // map of already colored letters

    for(auto i = 0; i < 5; ++i)
    {
        if(guess[i] == answer[i])
        {
            color[i] = '2';
            letters[answer[i]]++;
        }
    }

    for(auto i = 0; i < 5; ++i)
    {
        if(color[i] == '2')
            continue;

        auto n = std::count(answer.begin(), answer.end(), guess[i]);
        if(n > letters[guess[i]])
        {
            color[i] = '1';
            letters[guess[i]]++;
        }
    }

    return color;
}

std::string find_best_word(std::vector<std::string> &guesses, std::vector<std::string> &answers)
{
    auto best_guess = std::string();
    auto best_guess_count = 0;

    if(answers.size() <= 2)
        return answers[0];

    for(auto& guess : guesses)
    {
        auto elim_ctr = 0.0;

        auto colors = std::map<std::string, int>();

        for(auto& answer : answers)
            colors[find_color(guess, answer)]++;

        for(auto& [color, count] : colors)
        {
            auto elims = 0;
            for(auto& answer : answers)
            {
                if(find_color(guess, answer) != color)
                    elims++;
            }
            elim_ctr += elims * count;
        }


        auto thing = elim_ctr / answers.size();

        if(thing > best_guess_count)
        {
            best_guess = guess;
            best_guess_count = thing;
        }
    }

    //std::cout << "Best guess avg: " << best_guess_count << "\n";
    //std::cout << "Best guess: " << best_guess << "\n";

    return best_guess;
}

void thing(std::vector<std::string> &guesses, std::vector<std::string> &answers)
{
    if(answers.size() == 1)
    {
        std::cout << "\"" << answers[0] << "\","; // "THING",
        return;
    }
    auto guess = find_best_word(guesses, answers);
    std::cout << "{\"" << guess << "\":{"; // {"THING":{

    auto colors = std::vector<std::string>{};

    for(auto& answer : answers)
        colors.push_back(find_color(guess, answer));

    for(auto& color : colors)
    {
        std::cout << "\"" << color << "\":"; // "01210":
        auto new_answers = answers;

        new_answers.erase(std::remove_if(new_answers.begin(), new_answers.end(),
                                         [color, guess](std::string answer2){
            if(find_color(guess, answer2) != color)
                return true;
            else
                return false;
        }), new_answers.end());

        thing(guesses, new_answers);
    }
    std::cout << "}},"; // }},
}

int main(int argc, char const *argv[])
{
    auto answers = std::vector<std::string>{};
    auto guesses = std::vector<std::string>{};

    auto ansfile = std::ifstream("answers.txt");
    auto guessfile = std::ifstream("guesses.txt");

    if(!ansfile || !guessfile)
    {
        std::cout << "file issue\n";
        exit(1);
    }

    auto str = std::string();

    while(std::getline(ansfile, str))
    {
        answers.push_back(str);
    }

    str.clear();
    while(std::getline(guessfile, str))
    {
        guesses.push_back(str);
    }
    ansfile.close();
    guessfile.close();

    thing(guesses, answers);

    return 0;
}
