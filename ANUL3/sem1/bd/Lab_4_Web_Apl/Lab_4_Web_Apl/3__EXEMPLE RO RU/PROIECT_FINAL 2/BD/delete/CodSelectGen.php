<?php
        include_once '../conect.php';

        $sql = "SELECT idPopSex,Gen,Localitate,Anul,Populatie from popsex INNER JOIN sex ON popsex.idSex=sex.idSex INNER JOIN localitate ON popsex.idLocalitate=localitate.idLocalitate INNER JOIN an ON popsex.idAn=an.idAn ORDER by Localitate;";
        $result = mysqli_query($conn, $sql);
        $resultCheck = mysqli_num_rows($result);


        if ($resultCheck > 0) 
        {
                while ($row = mysqli_fetch_assoc($result)) 
                {
                        echo "<tr><td>" . $row['idPopSex'] . "</td><td>" . $row['Gen'] . "</td><td>" . $row['Populatie'] . "</td><td>" . $row['Anul'] . "</td><td>" . $row['Localitate'] . "</td></tr>";
                }
                        echo '</table>';
        }
?>
