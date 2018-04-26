import pandas as pd
import numpy as np
import os
import matplotlib.pyplot as plt
from datetime import datetime
from tkinter import ttk
from tkinter import *
import random
import scipy.signal
from scipy import fftpack, hamming
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis as LDA
from sklearn.linear_model import LogisticRegression
from sklearn.decomposition import PCA
from sklearn.metrics import confusion_matrix
from sklearn.ensemble import RandomForestClassifier
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.metrics import f1_score
from sklearn.model_selection import GridSearchCV
from sklearn.metrics import make_scorer
from time import sleep
import cv2
import pyautogui

# データ抽出
def  input(x):
    a1, a2, a3, a4, a5, a6, a7, a8, a9,a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45 = [x.iloc[250*3*i:256+250*3*i,0:8] for i in range(45)]
    return (a1, a2, a3, a4, a5, a6, a7, a8, a9,a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45)

def  input_tes(x):
    a1, a2, a3, a4, a5, a6, a7, a8, a9 = [x.iloc[250*5*i:256+250*5*i,0:8] for i in range(9)]

    return (a1, a2, a3, a4, a5, a6, a7, a8, a9)

def fft_t01(data, N, fs):
    dt = 1 /fs
    X = np.fft.fft(data)
    freq = np.linspace(0, 1.0/dt, N) # 周波数軸
    amplitudeSpectrum = [np.sqrt(c.real ** 2 + c.imag ** 2) for c in X]
    n = sum(amplitudeSpectrum)
    for i in range(len(amplitudeSpectrum)):
        amplitudeSpectrum[i] = amplitudeSpectrum[i]/n

    amplitudeSpectrum = np.array(amplitudeSpectrum)
    Spectrum =  amplitudeSpectrum[np.logical_and(freq>=3.0, freq<32)]
    am_sum = sum(Spectrum)
    a =  amplitudeSpectrum[np.logical_and(freq>=4, freq<8)]
    a = sum(a)
    p = a / am_sum

    return(p)

def fft_t02(data, N, fs):
    dt = 1 /fs
    X = np.fft.fft(data)
    freq = np.linspace(0, 1.0/dt, N) # 周波数軸
    amplitudeSpectrum = [np.sqrt(c.real ** 2 + c.imag ** 2) for c in X]
    n = sum(amplitudeSpectrum)
    for i in range(len(amplitudeSpectrum)):
        amplitudeSpectrum[i] = amplitudeSpectrum[i]/n

    amplitudeSpectrum = np.array(amplitudeSpectrum)
    Spectrum =  amplitudeSpectrum[np.logical_and(freq>=3.0, freq<32)]
    am_sum = sum(Spectrum)
    a =  amplitudeSpectrum[np.logical_and(freq>=8, freq<13)]
    a = sum(a)
    p = a / am_sum

    return(p)

def fft_t03(data, N, fs):
    dt = 1 /fs
    X = np.fft.fft(data)
    freq = np.linspace(0, 1.0/dt, N) # 周波数軸
    amplitudeSpectrum = [np.sqrt(c.real ** 2 + c.imag ** 2) for c in X]
    n = sum(amplitudeSpectrum)
    for i in range(len(amplitudeSpectrum)):
        amplitudeSpectrum[i] = amplitudeSpectrum[i]/n

    amplitudeSpectrum = np.array(amplitudeSpectrum)
    Spectrum =  amplitudeSpectrum[np.logical_and(freq>=3.0, freq<32)]
    am_sum = sum(Spectrum)
    a =  amplitudeSpectrum[np.logical_and(freq>=13, freq<20)]
    a = sum(a)
    p = a / am_sum

    return(p)


def time_separate(data,i):

    data1, data2, data3, data4 = [data[i:i+64] for i in range(0,250,64)]
    data_list = [data1, data2, data3, data4]

    a1 = data1.iloc[:, i]
    a2 = data2.iloc[:, i]
    a3 = data3.iloc[:, i]
    a4 = data4.iloc[:, i]

    x1 = fft_t01(a1,len(a1), 250)
    x2 = fft_t01(a2,len(a2), 250)
    x3 = fft_t01(a3,len(a3), 250)
    x4 = fft_t01(a4,len(a4), 250)

    x5 = fft_t02(a1,len(a1), 250)
    x6 = fft_t02(a2,len(a2), 250)
    x7 = fft_t02(a3,len(a3), 250)
    x8 = fft_t02(a4,len(a4), 250)

    x9 = fft_t03(a1,len(a1), 250)
    x10 = fft_t03(a2,len(a2), 250)
    x11 = fft_t03(a3,len(a3), 250)
    x12 = fft_t03(a4,len(a4), 250)

    return(x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12)

def get_train(text_data, t, label_list):
    colum_name=['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
    aso = pd.read_csv(text_data, index_col=0, header=None, names=colum_name)
    aso = aso.ix[6:, :8]
    start = int(t*250)
    aso = aso.ix[start:, :]

    a1, a2, a3, a4, a5, a6, a7, a8, a9,a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45 = input(aso)
    n = [a1, a2, a3, a4, a5, a6, a7, a8, a9,a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24, a25, a26, a27, a28, a29, a30, a31, a32, a33, a34, a35, a36, a37, a38, a39, a40, a41, a42, a43, a44, a45]
    features_df = pd.DataFrame()
    features_df['labels'] = label_list
    for i, j in zip(range(len(n)), n):
        x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12 = time_separate(j,0)
        features_df.loc[i, 'T1_s_1'] = x1
        features_df.loc[i, 'T2_s_1'] = x2
        features_df.loc[i, 'T3_s_1'] = x3
        features_df.loc[i, 'T4_s_1'] = x4
        features_df.loc[i, 'T1_a_1'] = x5
        features_df.loc[i, 'T2_a_1'] = x6
        features_df.loc[i, 'T3_a_1'] = x7
        features_df.loc[i, 'T4_a_1'] = x8
        features_df.loc[i, 'T1_b_1'] = x9
        features_df.loc[i, 'T2_b_1'] = x10
        features_df.loc[i, 'T3_b_1'] = x11
        features_df.loc[i, 'T4_b_1'] = x12

    for i, j in zip(range(len(n)), n):
        x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12 = time_separate(j,1)
        features_df.loc[i, 'T1_s_2'] = x1
        features_df.loc[i, 'T2_s_2'] = x2
        features_df.loc[i, 'T3_s_2'] = x3
        features_df.loc[i, 'T4_s_2'] = x4
        features_df.loc[i, 'T1_a_2'] = x5
        features_df.loc[i, 'T2_a_2'] = x6
        features_df.loc[i, 'T3_a_2'] = x7
        features_df.loc[i, 'T4_a_2'] = x8
        features_df.loc[i, 'T1_b_2'] = x9
        features_df.loc[i, 'T2_b_2'] = x10
        features_df.loc[i, 'T3_b_2'] = x11
        features_df.loc[i, 'T4_b_2'] = x12

    for i, j in zip(range(len(n)), n):
        x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12 = time_separate(j,2)
        features_df.loc[i, 'T1_s_3'] = x1
        features_df.loc[i, 'T2_s_3'] = x2
        features_df.loc[i, 'T3_s_3'] = x3
        features_df.loc[i, 'T4_s_3'] = x4
        features_df.loc[i, 'T1_a_3'] = x5
        features_df.loc[i, 'T2_a_3'] = x6
        features_df.loc[i, 'T3_a_3'] = x7
        features_df.loc[i, 'T4_a_3'] = x8
        features_df.loc[i, 'T1_b_3'] = x9
        features_df.loc[i, 'T2_b_3'] = x10
        features_df.loc[i, 'T3_b_3'] = x11
        features_df.loc[i, 'T4_b_3'] = x12

    for i, j in zip(range(len(n)), n):
        x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12 = time_separate(j,3)
        features_df.loc[i, 'T1_s_4'] = x1
        features_df.loc[i, 'T2_s_4'] = x2
        features_df.loc[i, 'T3_s_4'] = x3
        features_df.loc[i, 'T4_s_4'] = x4
        features_df.loc[i, 'T1_a_4'] = x5
        features_df.loc[i, 'T2_a_4'] = x6
        features_df.loc[i, 'T3_a_4'] = x7
        features_df.loc[i, 'T4_a_4'] = x8
        features_df.loc[i, 'T1_b_4'] = x9
        features_df.loc[i, 'T2_b_4'] = x10
        features_df.loc[i, 'T3_b_4'] = x11
        features_df.loc[i, 'T4_b_4'] = x12

    for i, j in zip(range(len(n)), n):
        x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12 = time_separate(j,4)
        features_df.loc[i, 'T1_s_5'] = x1
        features_df.loc[i, 'T2_s_5'] = x2
        features_df.loc[i, 'T3_s_5'] = x3
        features_df.loc[i, 'T4_s_5'] = x4
        features_df.loc[i, 'T1_a_5'] = x5
        features_df.loc[i, 'T2_a_5'] = x6
        features_df.loc[i, 'T3_a_5'] = x7
        features_df.loc[i, 'T4_a_5'] = x8
        features_df.loc[i, 'T1_b_5'] = x9
        features_df.loc[i, 'T2_b_5'] = x10
        features_df.loc[i, 'T3_b_5'] = x11
        features_df.loc[i, 'T4_b_5'] = x12

    for i, j in zip(range(len(n)), n):
        x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12 = time_separate(j,5)
        features_df.loc[i, 'T1_s_6'] = x1
        features_df.loc[i, 'T2_s_6'] = x2
        features_df.loc[i, 'T3_s_6'] = x3
        features_df.loc[i, 'T4_s_6'] = x4
        features_df.loc[i, 'T1_a_6'] = x5
        features_df.loc[i, 'T2_a_6'] = x6
        features_df.loc[i, 'T3_a_6'] = x7
        features_df.loc[i, 'T4_a_6'] = x8
        features_df.loc[i, 'T1_b_6'] = x9
        features_df.loc[i, 'T2_b_6'] = x10
        features_df.loc[i, 'T3_b_6'] = x11
        features_df.loc[i, 'T4_b_6'] = x12

    for i, j in zip(range(len(n)), n):
        x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12 = time_separate(j,6)
        features_df.loc[i, 'T1_s_7'] = x1
        features_df.loc[i, 'T2_s_7'] = x2
        features_df.loc[i, 'T3_s_7'] = x3
        features_df.loc[i, 'T4_s_7'] = x4
        features_df.loc[i, 'T1_a_7'] = x5
        features_df.loc[i, 'T2_a_7'] = x6
        features_df.loc[i, 'T3_a_7'] = x7
        features_df.loc[i, 'T4_a_7'] = x8
        features_df.loc[i, 'T1_b_7'] = x9
        features_df.loc[i, 'T2_b_7'] = x10
        features_df.loc[i, 'T3_b_7'] = x11
        features_df.loc[i, 'T4_b_7'] = x12

    for i, j in zip(range(len(n)), n):
        x1, x2, x3, x4, x5, x6, x7, x8, x9, x10, x11, x12 = time_separate(j,7)
        features_df.loc[i, 'T1_s_8'] = x1
        features_df.loc[i, 'T2_s_8'] = x2
        features_df.loc[i, 'T3_s_8'] = x3
        features_df.loc[i, 'T4_s_8'] = x4
        features_df.loc[i, 'T1_a_8'] = x5
        features_df.loc[i, 'T2_a_8'] = x6
        features_df.loc[i, 'T3_a_8'] = x7
        features_df.loc[i, 'T4_a_8'] = x8
        features_df.loc[i, 'T1_b_8'] = x9
        features_df.loc[i, 'T2_b_8'] = x10
        features_df.loc[i, 'T3_b_8'] = x11
        features_df.loc[i, 'T4_b_8'] = x12


    #X_train = features_df.ix[:, 1:]
    #y_train = features_df.ix[:, 0]

    return(features_df)

os.chdir("/Applications/SavedData")
#feature_df = get_train("aso_train.txt")
list01 = [1,2,0,1,1,0,2,1,2,1,2,0,2,1,0,1,2,0,1,2,1,0,1,0,2,1,0,1,2,1,0,0,1,2,1,0,2,1,0,2,1,2,0,2,1]
list02 = [1,2,0,0,2,1,2,1,2,1,0,0,2,1,2,1,2,0,2,1,0,2,1,0,1,2,0,1,0,1,2,1,0,1,0,1,2,1,2,0,0,2,0,1,0]
list03 = [1,0,2,1,0,2,2,1,2,0,1,2,0,1,2,1,0,1,0,2,1,0,2,2,1,1,0,0,1,0,2,2,0,1,2,1,2,0,1,2,0,1,2,0,1]

feature_df01 = get_train("OpenBCI-RAW-ita01.txt", 6.67, list01)
feature_df02 = get_train("OpenBCI-RAW-ita02.txt", 7.14, list02)
feature_df03 = get_train("OpenBCI-RAW-ita03.txt", 7.52, list03)

train_feature = pd.concat([feature_df01, feature_df02, feature_df03])
#train_feature = train_feature.sample(frac=1, random_state=0).reset_index(drop=True)

print(train_feature.shape)

labels = train_feature['labels']
labels = np.array(labels.values.flatten())
del train_feature['labels']

pca = PCA(n_components=45)
pca.fit(train_feature)
train_feature = pca.transform(train_feature)
print('累積寄与率: {0}'.format(sum(pca.explained_variance_ratio_)))

train_feature = pd.DataFrame(train_feature)

X_train = train_feature.ix[:89, :]
y_train = labels[:90]

X_test1 = train_feature.ix[90:104, :]
y_test1 = labels[90:105]

lda = LDA(n_components=2)
lda.fit(X_train, y_train)
X_train = lda.transform(X_train)
X_test1 = lda.transform(X_test1)

print('累積寄与率: {0}'.format(sum(lda.explained_variance_ratio_)))
"""
temp = pd.DataFrame(X_train)
temp["Outcome"] = y_train

print(temp)

aa = temp[temp['Outcome'] == 0]
bb = temp[temp['Outcome'] == 1]
cc = temp[temp['Outcome'] == 2]

print(aa)

plt.scatter(x=aa[0], y=aa[1], marker='o', color='red')
plt.scatter(x=bb[0], y=bb[1], marker='o', color='salmon')
plt.scatter(x=cc[0], y=cc[1], marker='o', color='orange')

plt.show()

print('累積寄与率: {0}'.format(sum(lda.explained_variance_ratio_)))
#print(X_train.shape)
#pca = PCA(n_components=40)
#X_test = pca.fit_transform(X_test)
#print('累積寄与率: {0}'.format(sum(lda.explained_variance_ratio_)))
#print(X_train.shape)
"""

"""
plt.bar([n for n in range(1, len(pca.explained_variance_ratio_)+1)], pca.explained_variance_ratio_)
plt.ylabel("contribution")
plt.xlabel("components")

plt.show()
"""
"""
# ハイパーパラメータ
forest_grid_param = {"n_estimators":[10,20,50,80,100,200],"max_depth":[i for i in range(1,6,1)], 'min_samples_split' : [3, 5, 10, 15, 20, 25, 30, 40, 50, 100], 'max_features': [1, 'auto', None]}
# スコア方法をF1に設定
f1_scoring = make_scorer(f1_score, pos_label=1, average='micro')

# グリッドサーチで学習
forest_grid_search = GridSearchCV(RandomForestClassifier(random_state=0, n_jobs=-1), forest_grid_param, scoring=f1_scoring, cv=4)
forest_grid_search.fit(X_train, y_train)

# 結果
print('Best parameters: {}'.format(forest_grid_search.best_params_))
print('Best score: {:.3f}'.format(forest_grid_search.best_score_))
"""

forest = RandomForestClassifier(n_estimators=200, min_samples_split=15, max_depth=3, max_features=None)
forest.fit(X_train, y_train)

#y_test1 = forest.predict(X_test1)
w1 = f1_score(y_test1, forest.predict(X_test1),average = 'micro')


print(w1)
