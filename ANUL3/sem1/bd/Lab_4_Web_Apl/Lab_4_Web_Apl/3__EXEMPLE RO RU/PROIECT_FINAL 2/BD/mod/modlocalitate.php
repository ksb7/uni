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


<div id="form1">
    <h3>Modificare de Localitate</h3>
    <form action="CodModLoc.php" method="POST">
        <input type="text" name="Id" placeholder="Introdu Id-ul pe care doresti sa-l modifici">
        <br>
        <br>
        <input type="text" name="Name" placeholder="Introdu Numele Nou!">
        <br>
                <br>
                <input type="radio" name="mediu" value="1"> Rural<br>
                <input type="radio" name="mediu" value="2"> Urban<br>  
                <br> 
        <br>
        <br>
        
        <button type="submit" name="submit">Introdu</button>
    </form>
</div>

<div id="tabprezent">
    <br>
        <table>
                <tr>
                        <th>idLocalitate</th>
                        <th>Localitatea</th>
                        <th>Mediul</th>

                </tr>


            <?php
                    include_once 'CodSelectLocMed.php';
            ?>

        </table>  
    <br>
</div>

</body>
</html>




