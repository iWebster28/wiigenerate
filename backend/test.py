# import joblib
# import numpy as np
# print(joblib.__version__)

# model = joblib.load("model.pkl")
# print(model(np.random.random((1,5))))


# `conda activate tf` in iterm to get tensroflow working on m1 mac

import tensorflow as tf
from music21 import *
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import Dropout
from keras.layers import LSTM
from keras.layers import Activation
import tensorflow as tf
from pygame import *
import numpy as np


# model = Sequential()
# model.add(LSTM(256, input_shape=(20, 1), return_sequences=True))
# model.add(Dropout(0.2))
# model.add(LSTM(256, return_sequences=True))
# model.add(Dropout(0.2))
# model.add(LSTM(256, input_shape=(20, 1), return_sequences=False))
# model.add(Dropout(0.2))
# model.add(Dense(164)) # from `n_vocab``
# model.add(Activation('softmax'))
# model.compile(loss='categorical_crossentropy', optimizer='rmsprop')

# model.load_weights('model/variables/variables.data-00000-of-00001')
# loss, acc = model.evaluate('', '', verbose=2)


new_model = tf.keras.models.load_model('model')
new_model.summary()


network_input = np.array([81, 90, 71, 125, 81, 90, 118, 99, 156, 88, 66, 159, 143, 66, 159, 88, 137, 124, 117, 61])
network_output = np.array([81, 90, 71, 125, 81, 90, 118, 99, 156, 88, 66, 159, 143, 66, 159, 88, 137, 124, 117, 61])
loss, acc = new_model.predict(network_input, verbose=2)
# print('Restored model, accuracy: {:5.2f}%'.format(100 * acc))