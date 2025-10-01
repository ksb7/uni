<!DOCTYPE html>
<html>
<head>
    <title>Recesamantul Republicii Moldova</title>
    <link rel="stylesheet" type="text/css" href="../style.css">
    <link rel="icon" type="image/ico" href="img/moldova.png">
    <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>

<header>
    <div class="headimg">
        <div>
            <a href="../index.php" id="textfp"><img id="iconfp" src="img/Moldova-256.png">Recesamantul Republicii Moldova</a>
        </div>
        <div>
            <div class="dropdown" style="float:right;">
              <img style=" margin-top: -100%;  height: 55px;width: 55px;" src="img/sound-05-512.png">
              <div class="dropdown-content">
                    <a id="textp" href="../recensamante.html"><img id="iconp" src="img/people_crowd-256.png">Recensamante</a>
                    <a id="textp" href="../statistic.php"><img id="iconp" src="img/chart-256.png">Statistici</a>
                    <a id="textp" href="../modify.html"><img id="iconp" src="img/283-256.png">Modificarea</a>
                    <a id="textp" href="../adaugare.html"><img id="iconp" src="img/packing-256.png">Adaugarea</a>
                    <a id="textp" href="../delete.html"><img id="iconp" src="img/Streamline-70-256.png">Stergerea</a>
                    <a id="textp" href="../download.php"><img id="iconp"  src="img/download-256.png">Download</a>
            </div>
        </div>
    </div>
</header>


<div id="form2">
    <h3>Introdu o Localitate si Etnia populatiei</h3>
    <br>
    <form action="CodAddEtn.php" method="POST">

            <input type="radio" name="Etnie" value="1"> Rusi<br>
            <input type="radio" name="Etnie" value="2"> Ukraineni<br>
            <input type="radio" name="Etnie" value="3"> Romani<br>
            <input type="radio" name="Etnie" value="4"> Moldoveni<br>
            <input type="radio" name="Etnie" value="5"> Gagauzi<br>
            <input type="radio" name="Etnie" value="6"> Bulgari<br> 

        <div>
            <br>
            <input type="radio" name="anul" value="1"> 2004<br>
            <input type="radio" name="anul" value="2"> 2014<br>
            <br>  
        </div>
        <input type="text" name="pop" placeholder="Introdu Populatia"><br>
        <input type="text" name="loc" placeholder="Introdu Id-ul Localitatii"><br><br>

        <button type="submit" name="submit">Introdu</button>
    </form>
</div>

<div id="tabprezent">
    <br>
        <table>
                <tr>
                        <th>idLocalitate</th>
                        <th>Localitatea</th>
                </tr>


            <?php
                    include_once 'CodSelectLoc.php';
            ?>

        </table>  
    <br>
</div>


</body>
</html>
