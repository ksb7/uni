<?php
        include_once '../conect.php';

        $sql = "SELECT idLocalitate,Localitate,Mediul FROM localitate INNER JOIN mediul on localitate.idMediu=mediul.idMediu ORDER BY idLocalitate;";
        $result = mysqli_query($conn, $sql);
        $resultCheck = mysqli_num_rows($result);


        if ($resultCheck > 0) 
        {
                while ($row = mysqli_fetch_assoc($result)) 
                {
                        echo "<tr><td>" . $row['idLocalitate'] . "</td><td>" . $row['Localitate'] . "</td><td>" . $row['Mediul'] . "</td></tr>";
                }
                        echo '</table>';
        }
?>
