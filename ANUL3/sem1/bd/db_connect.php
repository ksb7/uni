<?php
$mysqli = new mysqli("localhost", "root", "", "alegeri");

if ($mysqli->connect_error) {
    die("Conectare eșuată: " . $mysqli->connect_error);
}
?>
