#!/usr/bin/python
""" First example code on Tensorflow tutorial community.
	Classifying fashion articles from keras Dataset.
	references: 	
		https://www.tensorflow.org/tutorials/keras/basic_classification
		https://www.tensorflow.org/api_docs/python/tf
"""

from tensorflow.keras.datasets import fashion_mnist
from tensorflow.keras.layers import Dense, Flatten
from tensorflow.keras.models import Sequential
from tensorflow.keras.optimizers import Adam
import numpy as np

import matplotlib.pyplot as plt 

# Download database
(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()
class_names = ['T_shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat', 'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']
print "Dataset downloaded and class names defined."
"""
# Scaling 0 - 1
train_images = train_images/255.0
test_images  = test_images/ 255.0

plt.figure(figsize=(10,10))
for i in range(25):
    plt.subplot(5,5,i+1)
    plt.xticks([])
    plt.yticks([])
    plt.grid(False)
    plt.imshow(train_images[i], cmap=plt.cm.binary)
    plt.xlabel(class_names[train_labels[i]])
"""
# Model setup
model = Sequential([
	Flatten(input_shape=(28,28)),
	Dense(50, activation='relu'),
	Dense(50, activation='relu'),
	Dense(50, activation='relu'),
	Dense(50, activation='relu'),
	Dense(50, activation='relu'),
	Dense(10,  activation='softmax')]) #num of classes is 10
# Compiling the model
model.compile(
	optimizer= Adam(),
	loss = 'sparse_categorical_crossentropy',
	metrics = ['accuracy'])
# Training the model
model.fit(train_images, train_labels, epochs=10, validation_split = 0.2)
model.summary()
# Testing it.
test_loss, test_acc = model.evaluate(test_images, test_labels)
predictions = model.predict(test_images) #raw output
# Predictions
print (predictions)
model.save('Estudo/Tensorflow/models/model1.h5')

"""
# Defining functions to get some cool tables.
def plot_image(i, predictions_array, true_label, img):
	predictions_array, true_label, img = predictions_array[i], true_label[i], img[i]
	plt.grid(False)
	plt.xticks([])
	plt.yticks([])
	plt.imshow(img, cmap=plt.cm.binary)
	predicted_label = np.argmax(predictions_array)
	if predicted_label == true_label:
		color = 'blue'
	else:
		color = 'red'

	plt.xlabel("{} {:2.0f}% ({})".format(class_names[predicted_label],
		100*np.max(predictions_array),
		class_names[true_label]),
		color = color)

def plot_value_array(i, predictions_array, true_label):
	predictions_array, true_label = predictions_array[i], 	true_label[i]
	plt.grid(False)
	plt.xticks([])
	plt.yticks([])
	thisplot = plt.bar(range(10), predictions_array, color = '#777777')
	plt.ylim([0, 1])
	predicted_label = np.argmax(predictions_array)

	thisplot[predicted_label].set_color('red')
	thisplot[true_label].set_color('blue')

# Plotting images with their predictions
num_rows, num_cols = 5, 3
num_images = num_cols*num_rows
plt.figure(figsize=(2*2*num_cols, 2*num_rows))
for i in range(num_images):
	plt.figure(figsize=(6,3))
	plt.subplot(1,2,1)
	plot_image(i, predictions, test_labels, test_images)
	plt.subplot(1,2,2)
	plot_value_array(i, predictions,  test_labels)
plt.show()

# Using the trained model to make a prediction about a single image.
img = test_images[0]
print (img.shape)
print "Adding image to a list..."
img = (np.expand_dims(img,0))
print (img.shape)
predictions_single = model.predict(img)
print (predictions_single)
# Plot table
plot_value_array(0, predictions_single, test_labels)
_ = plt.xticks(range(10), class_names, rotation=45)
plt.show()
"""
