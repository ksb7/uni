<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  $temperature = $_POST['temperature'];
  $humidity = $_POST['humidity'];
  
  // Update the webpage with the received data
  echo "Temperature: $temperature°C<br>";
  echo "Humidity: $humidity%";
} else {
  echo "Invalid request method";
}
?>
