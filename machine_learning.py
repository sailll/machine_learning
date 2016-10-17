import csv
import glob
import numpy as np
import matplotlib.pyplot as plt
import math
plt.figure(1)


def multiply(theta, data):
    m = len(theta)
    sum = 0.0
    for i in range(m):
        sum = sum + theta[0] * data[0]
    return sum


def costfunction(theta, data, yi, xj):
    change = (multiply(theta, data) - yi) * xj
    return change


def gradient_descent(theta, dataset, y, xj):
    m = len(y)
    result = 0.0
    for i in range(m):
        result = result + costfunction(theta, dataset[i], y[i], xj)
    return result / m


csvlst = glob.glob("/Users/caizhongmou/Desktop/*.csv")
readerlst = list()
dataset = list()
GOOGcsv = "/Users/caizhongmou/Desktop/WIKI-GOOG.csv"
with open(GOOGcsv) as Gc:
    spamreader = csv.reader(Gc, delimiter=' ', quotechar='|')
    count = 0
    for row in spamreader:
        if(count == 0):
            count = count + 1
            continue
        tl = list()
        tl.append(1)
        dataset.append(tl)
for c in csvlst:
    with open(c) as lst:
        spamreader = csv.reader(lst, delimiter=' ', quotechar='|')
        k = 0
        count = 0
        for row in spamreader:
            if(count == 0):
                count = 1
                continue
            s = list()
            for i in row[0].split(',')[1:6]:
                s.append(float(i))
            dataset[k].extend(s)
            k = k + 1
            if(k >= len(dataset)):
                break
theta = [1] * 20
y = list()
for k in dataset[50:]:
    y.append(k[19])
    k.remove(k[19])
my = list()
for k in y:
    ty = list()
    ty.append(k)
    my.append(ty)
my2 = np.matrix(my)
se = np.matrix(dataset[50:])
ans = (se.getT() * se).getI() * se.getT() * my2
nans = np.array(ans)
origianal_price = y[0:50]
deviation = []
for k in dataset[0:50]:
    s = 0
    for i in range(20):
        s += nans[i][0] * k[i]
    deviation.append(s)
print deviation
err = 0.0
for k in range(len(deviation)):
    err += math.pow((deviation[k] - origianal_price[k]), 2)
err /= sum(deviation)
print err

l_rate = 0.00001
learning_count_max = 2000
for i in range(learning_count_max):
    tmp_theta = list()
    for j in range(len(theta)):
        for m in range(len(dataset)):
            t = theta[j] - l_rate * \
                gradient_descent(theta, dataset, y, dataset[m][j])
        tmp_theta.append(t)
    theta = [i for i in tmp_theta]
    print multiply(theta, dataset[0])
