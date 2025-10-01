<?php
require_once('config.sql.php');
session_start();
set_time_limit(0);
require_once('functions.php');
popupjs();
?>
<h3> Administrare studenti:</h3>
<ul>
<li><a href="<?php echo make_link('insert.php','400','400',0); ?>"> Introducere Studenti </a></li>
<li><a href="<?php echo make_link('vizualizare.php','700','400',1); ?>"> Vizualizare Studenti </a></li>
</ul>
<h3> Administrare catalog: </h3>
<ul>
<li><a href="<?php echo make_link('Modificare.php','700','400',0); ?>">Modificare catalog</a></li>
<li><a href="<?php echo make_link('catalog_meniu.php','700','400',0); ?>">Vizualizare catalog</a></li>
</ul>
<?