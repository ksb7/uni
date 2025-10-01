<?php
include 'db_connect.php';

$table = isset($_GET['table']) ? $_GET['table'] : 'primari';
$id = isset($_GET['id']) ? $_GET['id'] : null;

$localitati = $mysqli->query("SELECT id_localitate, nume_localitate FROM localitati");
$genuri = $mysqli->query("SELECT id_gen, nume_gen FROM genuri");
$partide = $mysqli->query("SELECT id_partid, nume_partid FROM partide");

//doar daca id e valid
if ($id) {
    $sql = "SELECT 
                p.id AS id,
                p.nume AS nume,
                p.prenume AS prenume,
                p.id_localitate AS localitate_id,
                p.id_functie AS functie_id,
                p.id_gen AS gen_id,
                p.id_partid AS partid_id
            FROM $table p
            WHERE p.id = $id";

    $result = $mysqli->query($sql);
    $row = $result->fetch_assoc();
}
?>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?php echo $id ? 'Editează' : 'Adaugă'; ?> <?php echo ucfirst($table); ?></title>
    <link rel="stylesheet" href="style.css">
</head>
<body>

<nav>
    <a href="index.php?table=primari">Primari</a>
    <a href="index.php?table=consilieri">Consilieri</a>
</nav>

<h1><?php echo $id ? 'Editează' : 'Adaugă'; ?> <?php echo ucfirst($table); ?></h1>

<form method="POST" action="save.php">
    <input type="hidden" name="id" value="<?php echo $id; ?>">
    <input type="hidden" name="table" value="<?php echo $table; ?>">

    <div class="form-group">
        <label for="nume">Nume:</label>
        <input type="text" name="nume" value="<?php echo isset($row['nume']) ? $row['nume'] : ''; ?>" required>
    </div>
    
    <div class="form-group">
        <label for="prenume">Prenume:</label>
        <input type="text" name="prenume" value="<?php echo isset($row['prenume']) ? $row['prenume'] : ''; ?>" required>
    </div>

    <div class="form-group">
        <label for="localitate">Localitate:</label>
        <select name="localitate" required>
            <option value="">Selectează Localitate</option>
            <?php while ($localitate = $localitati->fetch_assoc()) : ?>
                <option value="<?php echo $localitate['id_localitate']; ?>" <?php echo (isset($row['localitate_id']) && $row['localitate_id'] == $localitate['id_localitate']) ? 'selected' : ''; ?>>
                    <?php echo $localitate['nume_localitate']; ?>
                </option>
            <?php endwhile; ?>
        </select>
    </div>

    <div class="form-group">
        <label for="gen">Gen:</label>
        <select name="gen" required>
            <option value="">Selectează Gen</option>
            <?php while ($gen = $genuri->fetch_assoc()) : ?>
                <option value="<?php echo $gen['id_gen']; ?>" <?php echo (isset($row['gen_id']) && $row['gen_id'] == $gen['id_gen']) ? 'selected' : ''; ?>>
                    <?php echo $gen['nume_gen']; ?>
                </option>
            <?php endwhile; ?>
        </select>
    </div>

    <div class="form-group">
        <label for="partid">Partid:</label>
        <select name="partid" required>
            <option value="">Selectează Partid</option>
            <?php while ($partid = $partide->fetch_assoc()) : ?>
                <option value="<?php echo $partid['id_partid']; ?>" <?php echo (isset($row['partid_id']) && $row['partid_id'] == $partid['id_partid']) ? 'selected' : ''; ?>>
                    <?php echo $partid['nume_partid']; ?>
                </option>
            <?php endwhile; ?>
        </select>
    </div>

    <button type="submit" class="btn-submit"><?php echo $id ? 'Actualizează' : 'Adaugă'; ?></button>
</form>

</body>
</html>
