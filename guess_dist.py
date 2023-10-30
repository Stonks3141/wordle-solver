import sys, json, collections

def count(tree, depth=1, speed=collections.defaultdict(int)):
	_word, tree = list(tree.items())[0]
	if tree == {}:
		speed[depth] += 1
	else:
		for color, tree in tree.items():
			if isinstance(tree, str):
				speed[depth] += 1
			else:
				count(tree, depth + 1, speed)
	return speed

for i, ct in sorted(count(json.load(sys.stdin)).items()):
	print(f'{i}|{ct}')
