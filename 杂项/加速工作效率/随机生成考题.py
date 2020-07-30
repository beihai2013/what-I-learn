import random

print("按照试题库大小平均生成考题")

str = input("输入试题库数目：")
typeNumber = int(str)

print("输入各个试题库大小：")
number = []
sum = 0
for i in range(typeNumber):
	temp = int(input());
	number.append(temp);
	sum += temp

print("试题总数为：%d\n" % sum);


str = input("需要出的试题数：")
testNumber = int(str)
rest = testNumber;

for i in range(typeNumber):
        count = number[i] * testNumber / sum
        if i == typeNumber - 1:
                count = rest
        rest -= count
        print("第%d套题库，需要出%d道题，剩余%d道题,题号为：\n" % (i, count, rest))
        ss = []
        while len(ss) < count:
                temp = random.randint(1, number[i])
                if temp in ss:
                        continue
                ss.append(temp)
        ss.sort();
        for s in ss:
                print(s)
        
        
