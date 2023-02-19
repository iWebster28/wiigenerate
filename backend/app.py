# app.py
from flask import Flask
import base64
import music21
import np_utils
import pygame

import numpy as np

app = Flask(__name__)

# Clean ---

# Holds all possible notes and chords 
notes = []
with open('notes.txt', 'r') as notes_txt:
    notes_txt = notes_txt.read().split(',') 
    for note in notes_txt:
        notes.append(note)

sequence_length = 20 
pitchnames = sorted(set(item for item in notes))
note_to_int = dict((note, number) for number, note in enumerate(pitchnames))
prediction_filepath = 'predict.mid'


@app.route("/")
def hello():
    return "Hello, World!"

# Return the model prediction in MIDI format.
@app.route('/predict', method=['POST'])
def predict():
    # Load model
    # model = joblib.load("model.pkl")
    # print(model(np.random.random((1,5))))

    # # Organize 
    # start = np.random.randint(0, len(network_input)-1)
    # int_to_note = dict((number, note) for number, note in enumerate(pitchnames))

    # pattern = network_input[start]

    # prediction_output = []

    # for note_index in range(100): #here, we're generating 100 notes
    #     prediction_input = np.reshape(pattern, (1, len(pattern), 1))
    #     prediction_input = prediction_input / float(n_vocab)    
        
    #     prediction = model.predict(prediction_input, verbose=0)    
    #     index = np.argmax(prediction)

    #     result = int_to_note[index]
    #     prediction_output.append(result)    

    #     pattern.ravel()
    #     patternbeta =  pattern + index
    #     patternbeta = patternbeta[1:len(patternbeta)]

    # offset = 0
    # output_notes = []

    # for pattern in prediction_output:
    #     #chords!
    #     if ('.' in pattern) or pattern.isdigit():
    #         notes_in_chord = pattern.split('.')
    #         notes = [] #creating the array where we'll store the note values, which the for loop below will handle
    #         for current_note in notes_in_chord:
    #             new_note = note.Note(int(current_note))
    #             new_note.storedInstrument = instrument.Piano()
    #             notes.append(new_note)
    #         new_chord = chord.Chord(notes) #adding the note to the chord object
    #         new_chord.offset = offset #connecting it to the offset variable
    #         output_notes.append(new_chord) #adding it to the song
    #     #notes!
    #     else:
    #         new_note = note.Note(pattern) #storing it in the object
    #         new_note.offset = offset #connecting it to our offset command later on
    #         new_note.storedInstrument = instrument.Piano() #playing it with piano
    #         output_notes.append(new_note) #adding it to the song
    #     #make sure notes don't end up on top of each other by adding an 0.5 offset every time
    #     offset += 0.5


    # us = environment.UserSettings()
    # us.getSettingsPath()

    # # Model prediction
    # s = stream.Stream(output_notes)
    # mf = s.write('midi', fp=prediction_filepath)

    # Open midi 
    with open(prediction_filepath, mode='rb') as midi_file: 
        base64_encoded_bytes = base64.b64encode(midi_file.read())

    return f"{base64_encoded_bytes}" 