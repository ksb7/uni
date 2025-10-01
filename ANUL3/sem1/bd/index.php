<?php
include 'db_connect.php';

$table = isset($_GET['table']) ? $_GET['table'] : 'primari';

$filter_gen = $_GET['gen'] ?? '';
$filter_localitate = $_GET['localitate'] ?? '';
$filter_partid = $_GET['partid'] ?? '';

$conditions = [];
if (!empty($filter_gen)) {
    $conditions[] = "gen.nume_gen = '" . $mysqli->real_escape_string($filter_gen) . "'";
}
if (!empty($filter_localitate)) {
    $conditions[] = "l.nume_localitate = '" . $mysqli->real_escape_string($filter_localitate) . "'";
}
if (!empty($filter_partid)) {
    $conditions[] = "pa.nume_partid = '" . $mysqli->real_escape_string($filter_partid) . "'";
}

$where_clause = '';
if (!empty($conditions)) {
    $where_clause = 'WHERE ' . implode(' AND ', $conditions);
}

$sql = "SELECT 
            p.id AS id,
            CONCAT(p.nume, ' ', p.prenume) AS nume_complet,
            l.nume_localitate AS localitate,
            u.nume AS tip_localitate,
            gen.nume_gen AS gen,
            pa.nume_partid AS partid
        FROM $table p
        JOIN localitati l ON p.id_localitate = l.id_localitate
        JOIN unitate u ON l.id_unitate = u.id_unitate
        JOIN genuri gen ON p.id_gen = gen.id_gen
        JOIN partide pa ON p.id_partid = pa.id_partid
        $where_clause";

$result = $mysqli->query($sql);

$genuri = $mysqli->query("SELECT nume_gen FROM genuri");
$localitati = $mysqli->query("SELECT nume_localitate FROM localitati");
$partide = $mysqli->query("SELECT nume_partid FROM partide");
?>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Alegere Primari/Consilieri</title>
    <link rel="stylesheet" type="text/css" href="style.css">
</head>
<body>

<nav>
    <a href="index.php?table=primari">Primari</a>
    <a href="index.php?table=consilieri">Consilieri</a>
</nav>

<h1>Gestionare <?php echo ucfirst($table); ?></h1>

<form method="GET" action="index.php">
    <input type="hidden" name="table" value="<?php echo $table; ?>">
    <label for="gen">Filtrează după gen:</label>
    <select name="gen" id="gen">
        <option value="">Toate</option>
        <?php while ($row = $genuri->fetch_assoc()) : ?>
            <option value="<?php echo $row['nume_gen']; ?>" <?php echo $filter_gen == $row['nume_gen'] ? 'selected' : ''; ?>>
                <?php echo $row['nume_gen']; ?>
            </option>
        <?php endwhile; ?>
    </select>

    <label for="localitate">Filtrează după localitate:</label>
    <select name="localitate" id="localitate">
        <option value="">Toate</option>
        <?php while ($row = $localitati->fetch_assoc()) : ?>
            <option value="<?php echo $row['nume_localitate']; ?>" <?php echo $filter_localitate == $row['nume_localitate'] ? 'selected' : ''; ?>>
                <?php echo $row['nume_localitate']; ?>
            </option>
        <?php endwhile; ?>
    </select>

    <label for="partid">Filtrează după partid:</label>
    <select name="partid" id="partid">
        <option value="">Toate</option>
        <?php while ($row = $partide->fetch_assoc()) : ?>
            <option value="<?php echo $row['nume_partid']; ?>" <?php echo $filter_partid == $row['nume_partid'] ? 'selected' : ''; ?>>
                <?php echo $row['nume_partid']; ?>
            </option>
        <?php endwhile; ?>
    </select>

    <button type="submit">Filtrează</button>
</form>

<div class="actions">
    <a href="create.php?table=<?php echo $table; ?>" class="btn-add">Adaugă</a>
</div>

<table>
    <thead>
        <tr>
            <th>Nume</th>
            <th>Localitate</th>
            <th>Gen</th>
            <th>Partid</th>
            <th>Acțiuni</th>
        </tr>
    </thead>
    <tbody>
        <?php while ($row = $result->fetch_assoc()) : ?>
            <tr>
                <td><?php echo $row['nume_complet']; ?></td>
                <td>
                    <?php
                    switch ($row['tip_localitate']) {
                        case 'Comuna':
                            echo $row['localitate'] . ' (Com.)';
                            break;
                        case 'Oras':
                            echo $row['localitate'] . ' (Or.)';
                            break;
                        case 'Sat':
                            echo $row['localitate'] . ' (S.)';
                            break;
                        case 'Municipiu':
                            echo $row['localitate'] . ' (Mun.)';
                            break;
                        default:
                            echo $row['localitate'];
                    }
                    ?>
                </td>
                <td><?php echo $row['gen']; ?></td>
                <td><?php echo $row['partid']; ?></td>
                <td class="actions">
                    <a href="edit.php?id=<?php echo $row['id']; ?>&table=<?php echo $table; ?>">Editează</a>
                    <a href="delete.php?id=<?php echo $row['id']; ?>&table=<?php echo $table; ?>">Șterge</a>
                </td>
            </tr>
        <?php endwhile; ?>
    </tbody>
</table>

</body>
</html>
