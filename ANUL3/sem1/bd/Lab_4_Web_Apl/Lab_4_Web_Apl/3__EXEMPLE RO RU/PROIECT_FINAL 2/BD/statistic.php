<?php 

error_reporting(0);
ini_set('display_errors', 0);

$connect = mysqli_connect("localhost", "root", "", "lucraredean");

$searchq2 = $_POST['an'];
$searchq1 = $_POST['loc'];

$searchq1 = preg_replace("#^0-9a-z#i", "", $searchq1);
$searchq2 = preg_replace("#^0-9a-z#i", "", $searchq2);

$query = "SELECT Etnie,Populatie,Anul,Localitate from popetnii INNER JOIN etnii ON popetnii.idEtnie=etnii.idEtnie INNER JOIN an ON popetnii.idAn=an.idAn INNER JOIN localitate ON popetnii.idLocalitate=localitate.idLocalitate WHERE Localitate LIKE '%$searchq1%' AND Anul = $searchq2 ";


$result = mysqli_query($connect, $query);
$chart_data = '';
while($row = mysqli_fetch_array($result))
{
 $chart_data .= "{ etn:'".$row["Etnie"]."', pop:".$row["Populatie"].", anul:".$row["Anul"]."}, ";
}
$chart_data = substr($chart_data, 0, -2);
?>


<!DOCTYPE html>
<html>
 <head>
  <title>Recesamantul Republicii Moldova</title>
  <link rel="stylesheet" href="//cdnjs.cloudflare.com/ajax/libs/morris.js/0.5.1/morris.css">
  <link rel="stylesheet" type="text/css" href="style.css">
  <link rel="icon" type="image/ico" href="img/moldova.png">
  <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.0/jquery.min.js"></script>
  <script src="//cdnjs.cloudflare.com/ajax/libs/raphael/2.1.0/raphael-min.js"></script>
  <script src="//cdnjs.cloudflare.com/ajax/libs/morris.js/0.5.1/morris.min.js"></script>
  
 </head>
 <body>


<header>
    <div class="headimg">
        <div>
            <a href="index.php" id="textfp"><img id="iconfp" src="img/Moldova-256.png">Recesamantul Republicii Moldova</a>
        </div>
        <div>
          <div class="dropdown" style="float:right;">
        <img style=" margin-top: -100%;  height: 55px;width: 55px;" src="img/sound-05-512.png">
        <div class="dropdown-content">
            <a id="textp" href="recensamante.html"><img id="iconp" src="img/people_crowd-256.png">Recensamante</a>
              <a id="textp" href="statistic.php"><img id="iconp" src="img/chart-256.png">Statistici</a>
              <a id="textp" href="modify.html"><img id="iconp" src="img/283-256.png">Modificarea</a>
              <a id="textp" href="adaugare.html"><img id="iconp" src="img/packing-256.png">Adaugarea</a>
              <a id="textp" href="delete.html"><img id="iconp" src="img/Streamline-70-256.png">Stergerea</a>
              <a id="textp" href="download.php"><img id="iconp"  src="img/download-256.png">Download</a>
        </div>
    </div>
    </div>
</header>




  <br /><br />
  <div class="container"  style="width:80%;">
   <h2 align="center"></h2>

   <div id="">
	    <form action="statistic.php" method="post" id="dorm1" style="color: white; margin-left: 10%;"> 
          <div style="width: 20%; float:left;">       
            <input type="radio" name="loc" value="Chisinau" checked> Chisinau <br>
            <input type="radio" name="loc" value="Orhei"> Orhei <br>
            <input type="radio" name="loc" value="Balti"> Balti <br>
            <input type="radio" name="loc" value="Anenii Noi"> Anenii Noi <br>
            <input type="radio" name="loc" value="Soroca"> Soroca <br>
            <br>  
          </div>

           <div style="width: 10%; float:left;">       
            <input type="radio" name="an" value="2004" checked> 2004 <br>
            <br>  
          </div>

          <div style="width: 10%; float:left;">       
            <input type="radio" name="an" value="2014"> 2014 <br>
            <br>  
          </div>



            <br><br><br><br><br><br><br>
	        <input type="submit" value=">>"/>
	    </form>
	</div>

  <br><br>
   <h1 align="center"><?php echo $searchq1 ?></h1>   
   <br /><br />
   <div id="chart"></div>
  </div>
 </body>
</html>

<script>
Morris.Bar ({
 element : 'chart',
 data:[<?php echo $chart_data; ?>],
 xkey:'etn',
 ykeys:['pop'],
 labels:['Populatie'],
 hideHover:'auto',
 stacked:true,
 gridTextColor : 'white',
});
</script>