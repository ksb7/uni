<!DOCTYPE html>
<html>
<head>
    <title>Recesamantul Republicii Moldova</title>
    <link rel="stylesheet" type="text/css" href="style.css">
    <link rel="icon" type="image/ico" href="img/moldova.png">
    <meta name="viewport" content="width=device-width, initial-scale=1">
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
                    <a id="textp" href=""><img id="iconp" src="img/chart-256.png">Statistici</a>
                    <a id="textp" href="modify.html"><img id="iconp" src="img/283-256.png">Modificarea</a>
                    <a id="textp" href="adaugare.html"><img id="iconp" src="img/packing-256.png">Adaugarea</a>
                    <a id="textp" href="delete.html"><img id="iconp" src="img/Streamline-70-256.png">Stergerea</a>
                    <a id="textp" href="download.php"><img id="iconp"  src="img/download-256.png">Download</a>
            </div>
        </div>
    </div>
</header>

<div style="margin-top: 10%; color: white; text-align: center;">

    <h2 style="color: white;">Poti descarca fisierele de aici ↓ </h2><br><br>
    <a style="color: white;" href="download.php?file=Rec_anii_'59_'70_'79_'89_2004.xls">Populaţia la recensămintele din anii 1959, 1970, 1979, 1989 şi 2004, pe sexe şi medii, în profil teritorial</a><br><br>
    <a style="color: white;" href="download.php?file=Pop_mediu_loc_sex.xls">Populaţia pe medii, localităţi şi sexe, în profil teritoria</a><br><br>
    <a style="color: white;" href="download.php?file=Nationalitatea de baza.xls">Populaţia după naţionalităţile de bază, în profil teritorial</a><br><br>

</div>
</body>
</html>

 
<?php 
if(!empty($_GET['file']))
{
    $filename = basename($_GET['file']);
    $filepath = 'down/' . $filename;
    if(!empty($filename) && file_exists($filepath)){
 
//Define Headers
        header("Cache-Control: public");
        header("Content-Description: FIle Transfer");
        header("Content-Disposition: attachment; filename=$filename");
        header("Content-Type: application/zip");
        header("Content-Transfer-Emcoding: binary");
 
        readfile($filepath);
        exit;
 
    }
    else{
        echo "This File Does not exist.";
    }
}
 
 ?>





