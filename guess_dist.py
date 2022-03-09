import json

jfile = open('wordle.json')
data = json.load(jfile)
jfile.close()

ansfile = open('answers.txt')
answers = list()
for line in ansfile:
    answers.append(line.rstrip('\n'))
ansfile.close()

def findcolor(guess, answer):
    color = list('00000')
    letters = dict()
    for i in range(5):
        if guess[i] not in letters:
            letters[guess[i]] = 0
        if guess[i] == answer[i]:
            color[i] = '2'
            letters[guess[i]] += 1
    
    for i in range(5):
        if color[i] == '2':
            continue
        if answer.count(guess[i]) > letters[guess[i]]:
            color[i] = '1'
            letters[guess[i]] += 1
    
    return ''.join(color)

def func1(d, ans):
    a = list(d.keys())[0]
    c = findcolor(a, ans)
    if type(d[a][c]) == str:
        return 2
    return func1(d[a][c], ans) + 1
    
speed = {1:0, 2:0, 3:0, 4:0, 5:0, 6:0}
for answer in answers:
    print(answer)
    speed[func1(data, answer)] += 1;
print(speed)
