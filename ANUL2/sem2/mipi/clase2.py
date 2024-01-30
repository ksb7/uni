import matplotlib.pyplot 
import matplotlib.gridspec
import pandas

dataframe1 = pandas.read_excel("/home/kiu/Downloads/abilitate_economica.xlsx")
x_axis_dataframe1 = dataframe1["Activitati"]
y_axis_dataframe1 = dataframe1["total"]

dataframe2 = pandas.read_excel("/home/kiu/Downloads/educatie.xlsx")
x_axis_dataframe2 = dataframe2["Domeniul"]
y_axis_dataframe2 = dataframe2["Rata bruta"]

dataframe3 = pandas.read_excel("/home/kiu/Downloads/fertilitate.xlsx")
x_axis_dataframe3 = dataframe3["Grupa de varsta"]
y_axis_dataframe3 = dataframe3["fertilitatea"]

dataframe4 = pandas.read_excel("/home/kiu/Downloads/decizii.xlsx")
x_axis_dataframe4 = dataframe4["Domenii"]
y_axis_dataframe4 = dataframe4["Ponderea"]

gridspec = matplotlib.gridspec.GridSpec(2, 2)
fig = matplotlib.pyplot.figure(num="Grafice")

graph1 = fig.add_subplot(gridspec[1, 0])
graph1.hist(x_axis_dataframe1, edgecolor="black")
graph1.set_title("Abilitatea economica")
graph1.tick_params(axis="x", rotation=45, labelsize="xx-small")

graph2 = fig.add_subplot(gridspec[0, 1])
graph2.plot(x_axis_dataframe2.values, y_axis_dataframe2.values)
graph2.set_title("Educatia pe parcursul vietii")
graph2.tick_params(axis="x", rotation=45, labelsize="xx-small")

graph3 = fig.add_subplot(gridspec[0, 0])
graph3.pie(y_axis_dataframe3, labels=x_axis_dataframe3)
graph3.set_title("Fertilitatea")
graph3.tick_params(labelsize="xx-small")

graph4 = fig.add_subplot(gridspec[1, 1])
graph4.bar(x_axis_dataframe4, y_axis_dataframe4)
graph4.set_title("Sanatatea")
graph4.tick_params(axis="x", rotation=45, labelsize="xx-small")

fig.show()
