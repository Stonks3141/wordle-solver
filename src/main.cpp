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
        //std::cerr << "guessing:" << guess << " ";
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

std::vector<std::string> thing(std::vector<std::string> &guesses, std::vector<std::string> &answers, std::string answer, std::string guess)
{
    auto new_answers = answers;

    auto color = find_color(guess, answer);

    new_answers.erase(std::remove_if(new_answers.begin(), new_answers.end(),
                                     [color, guess](std::string answer2){
        if(find_color(guess, answer2) != color)
            return true;
        else
            return false;
    }), new_answers.end());

    //std::cout << "new size: " << new_answers.size() << "\n";

    if(new_answers.size() == 1)
    {
        std::cerr << new_answers[0] << " ";
        return {new_answers[0]};
    }
    else
    {
        auto t = find_best_word(guesses, new_answers);
        std::cerr << t << " ";
        if(t == answer)
            return {t};

        auto r = thing(guesses, new_answers, answer, t);
        r.insert(r.begin(), t);

        if(r.size() > 100)
        {
            std::cout << "uhoh\n";
            exit(1);
        }
        return r;
    }
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

    auto speed = std::map<int, int>();

    for(auto& ans : answers)
    {
        std::cerr << "roate ";
        auto a = thing(guesses, answers, ans, "roate");
        std::cout << "\n";
        speed[a.size()]++;
    }

    for(auto& [num, ct] : speed)
        std::cout << ct << " Wordles solved in " << num << " tries\n";

    return 0;
}
