<!doctype html>
<html lang="en">
<head>
  <title>Panoul administratorului</title>
</head>
<body>
  <?php
    $host = 'localhost';  // Hostul de lucru, este unul local, pe calculatorul dat
    $user = 'root';    // numele utilizatorului
    $pass = ''; // Parola utilizatorului
    $db_name = 'my_db';   // Numele BD
    $link = mysqli_connect($host, $user, $pass, $db_name); // Conectare cu BD

    // In caz daca nu am reusit sa conectezi BD
    if (!$link) {
      echo 'Nu pot conecta BD. Codul erorii: ' . mysqli_connect_errno() . ', Eroarea: ' . mysqli_connect_error();
      exit;
    }

    //Daca variabila Name a fost transmisa
    if (isset($_POST["Name"])) {
      //Daca aceasta interogare este pentru UPDATE-are, atunci efectuam modificarea datelor 
      if (isset($_GET['redactare_id'])) {
          $sql = mysqli_query($link, "UPDATE `products` SET `Name` = '{$_POST['Name']}',`Price` = '{$_POST['Price']}' WHERE `ID`={$_GET['redactare_id']}");
      } else {
      //In caz contrar INSERT, inseram datele prin intermediul inteorgarii respective 
          $sql = mysqli_query($link, "INSERT INTO `products` (`Name`, `Price`) VALUES ('{$_POST['Name']}', '{$_POST['Price']}')");
      }

      //Daca INSERT a decurs cu succes, atunci mention[m acest fapt
      if ($sql) {
        echo '<p>Inserare cu Succes! Felicitari!</p>';
      } else {
        echo '<p>Ati comis o eroare!?: ' . mysqli_error($link) . '</p>';
      }
    }

    if (isset($_GET['deletare_id'])) { //Verificam daca exista vre-o variabila?
      //Distrugem inscrierea din tabelul de lucru
      $sql = mysqli_query($link, "DELETE FROM `products` WHERE `ID` = {$_GET['deletare_id']}");
      if ($sql) {
        echo "<p>DELETE efectuat cu succes! Felicitari??!!!</p>";
      } else {
        echo '<p>Ati comis o eroare!?: ' . mysqli_error($link) . '</p>';
      }
    }

    //daca ati transmis variabila de lucru redactare_id, atunci urmeaza sa modificati/reinoiti datele. Dar mai intii s[ le selectam din BD
    if (isset($_GET['redactare_id'])) {
      $sql = mysqli_query($link, "SELECT `ID`, `Name`, `Price` FROM `products` WHERE `ID`={$_GET['redactare_id']}");
      $product = mysqli_fetch_array($sql);
    }
  ?>
  <form action="" method="post">
    <table>
      <tr>
        <td>Denumirea:</td>
        <td><input type="text" name="Name" value="<?= isset($_GET['redactare_id']) ? $product['Name'] : ''; ?>"></td>
      </tr>
      <tr>
        <td>Pretul:</td>
        <td><input type="text" name="Price" size="3" value="<?= isset($_GET['redactare_id']) ? $product['Price'] : ''; ?>"> lei.</td>
      </tr>
      <tr>
        <td colspan="2"><input type="submit" value="OK"></td>
      </tr>
    </table>
  </form>
  <table border='1'>
    <tr>
      <td>Identificatorр</td>
      <td>Denumirea</td>
      <td>Pret</td>
      <td>Deletare</td>
      <td>Modificare</td>
    </tr>
    <?php
      $sql = mysqli_query($link, 'SELECT `ID`, `Name`, `Price` FROM `products`');
      while ($result = mysqli_fetch_array($sql)) {
        echo '<tr>' .
             "<td>{$result['ID']}</td>" .
             "<td>{$result['Name']}</td>" .
             "<td>{$result['Price']} ₽</td>" .
             "<td><a href='?deletare_id={$result['ID']}'>Deletare</a></td>" .
             "<td><a href='?redactare_id={$result['ID']}'>Modificare</a></td>" .
             '</tr>';
      }
    ?>
  </table>
  <p><a href="?add=new">INSERT - inseram un nou produs</a></p>
</body>
</html>