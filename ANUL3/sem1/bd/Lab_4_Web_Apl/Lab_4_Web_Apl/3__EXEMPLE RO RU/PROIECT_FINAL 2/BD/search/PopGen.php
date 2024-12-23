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

<div id="tabselect">
	<div id="form2">
	    <form action="PopGen.php" method="post" id="dorm1"> 
	        <input type="text" name="localitate" placeholder="Introdu Localitatea"/>
	        <input type="text" name="gen" placeholder="Introdu Genul"/>
            <input type="text" name="mediu" placeholder="Introdu Mediul"/>
            <input type="text" name="an" placeholder="Introdu Anul"/>
            <br><br>
	        <input type="submit" value=">>"/>
	    </form>
	</div>
	<div>
	  	<table class="center">
	            <tr>
	                	<th>Localitate</th>
	                    <th>Gen</th>
                        <th>Mediul</th>
	                    <th>Populatia</th>
	                    <th>Anul</th>
	            </tr>


	        <?php
	                include_once 'SelectPopGen.php';
	        ?>
	    </table>
	</div>
</div>

</body>
</html>