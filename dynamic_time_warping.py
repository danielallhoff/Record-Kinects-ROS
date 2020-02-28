
#python -m pip install dtw
from dtw import dtw
import numpy as np
from sklearn.model_selection import train_test_split
#Using manhattan
dtw_distance = lambda x,y: np.abs(x-y)

#Randomise samples(interchange actions)
def preprocess_data(X,y):
    for sample in range(0, X.size):


#Returns behaviour with best match.
def dtw_predict(X, y, tiseq_predict):
    predictions = []
    for p in range(0,X.size()):
        
        d, cost_matrix, acc_cost_matrix, path = dtw(p, tiseq_predict, dist=dtw_distance)
        predictions.append(acc_cost_matrix)
    return y[np.argmax(predictions)]
def test(X_train, y_train, X_test, y_test):
    hits = 0
    
    for i in range(0,X_test.size()):
        behaviour = dynamic_time_warping(X_train, y_train, X_test[i])
        
        if behaviour == y_test[i]: hits +=1
    
    return hits/X_test.size()*1.0


#From csv file a input is: behaviour; action1(frame 1); action2(frame 2); ...
def load_data():
    return "data"

def main():
    #np arrays
    X, y = load_data()
    X_train, X_test, y_train, y_test = train_test_split(X,y,test_size=0.10, random_state=42)

if __name == "__main__":
    main()