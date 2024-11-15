<?php
        include_once '../conect.php';

        $sql = "SELECT IdPopSex,Gen,Populatie,Anul,Localitate FROM popsex INNER JOIN sex on popsex.idSex=sex.idSex INNER JOIN an on popsex.idAn=an.idAn INNER JOIN localitate on popsex.idLocalitate=localitate.idLocalitate ORDER BY IdPopSex;";
        $result = mysqli_query($conn, $sql);
        $resultCheck = mysqli_num_rows($result);


        if ($resultCheck > 0) 
        {
                while ($row = mysqli_fetch_assoc($result)) 
                {
                        echo "<tr><td>" . $row['IdPopSex'] . "</td><td>" . $row['Localitate'] . "</td><td>" . $row['Gen'] . "</td><td>" . $row['Populatie'] . "</td><td>" . $row['Anul'] . "</td></tr>";
                }
                        echo '</table>';
        }
?>
