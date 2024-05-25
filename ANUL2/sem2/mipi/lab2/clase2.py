import matplotlib.pyplot 
import matplotlib.gridspec
import pandas

# Primul tabel
dataframe1 = pandas.read_excel("C:/Users/crist/Downloads/uni/ANUL2/sem2/mipi/abilitate_economica.xlsx")
x_axis_dataframe1 = dataframe1["Activitati"]
y_axis_dataframe1 = dataframe1["total"]

# Al doilea tabel
dataframe2 = pandas.read_excel("C:/Users/crist/Downloads/uni/ANUL2/sem2/mipi/educatie.xlsx")
x_axis_dataframe2 = dataframe2["Domeniul"]
y_axis_dataframe2 = dataframe2["Rata bruta"]

# Al treilea tabel
dataframe3 = pandas.read_excel("C:/Users/crist/Downloads/uni/ANUL2/sem2/mipi/fertilitate.xlsx")
x_axis_dataframe3 = dataframe3["Grupa de varsta"]
y_axis_dataframe3 = dataframe3["fertilitatea"]

# Al patrulea tabel
dataframe4 = pandas.read_excel("C:/Users/crist/Downloads/uni/ANUL2/sem2/mipi/decizii.xlsx")
x_axis_dataframe4 = dataframe4["Domenii"]
y_axis_dataframe4 = dataframe4["Ponderea"]

# Crearea sub graficelor
gridspec = matplotlib.gridspec.GridSpec(2, 2)
fig = matplotlib.pyplot.figure(num="Statistica pe genul feminin")

# Primul grafic - histograma
graph1 = fig.add_subplot(gridspec[1, 0])
graph1.hist(x_axis_dataframe1, bins = 5, edgecolor="black")
graph1.set_xticklabels(list(x_axis_dataframe1))
graph1.set_ylabel("Frecventa")
graph1.set_title("Disparitatea salariala pe domenii")
graph1.tick_params(axis="x", rotation=45, labelsize="xx-small")

# Al doilea subgrafic - grafic
graph2 = fig.add_subplot(gridspec[0, 1])
graph2.plot(x_axis_dataframe2.values, y_axis_dataframe2.values)
graph2.legend(["Rata Bruta"])
graph2.set_title("Educatia pe parcursul vietii")
graph2.tick_params(axis="x", labelsize="xx-small")

# Al treilea subgrafic - circular
graph3 = fig.add_subplot(gridspec[0, 0])
graph3.pie(y_axis_dataframe3, labels=x_axis_dataframe3)
graph3.set_title("Fertilitatea feminina la adolescente")
graph3.tick_params(labelsize="xx-small")

# Al patrulea subgrafic - bare
graph4 = fig.add_subplot(gridspec[1, 1])
graph4.bar(x_axis_dataframe4, y_axis_dataframe4)
graph4.set_title("Ponderea femeilor in luarea deciziilor")
graph4.tick_params(axis="x", rotation=45, labelsize="xx-small")

# Crearea graficului
fig.show()
