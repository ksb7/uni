<?php
        include_once '../conect.php';

        $sql = "SELECT idPopEtnie,Etnie,Localitate,Anul,Populatie from popetnii INNER JOIN etnii ON popetnii.idEtnie=etnii.idEtnie INNER JOIN localitate ON popetnii.idLocalitate=localitate.idLocalitate INNER JOIN an ON popetnii.idAn=an.idAn ORDER by Localitate;";
        $result = mysqli_query($conn, $sql);
        $resultCheck = mysqli_num_rows($result);


        if ($resultCheck > 0) 
        {
                while ($row = mysqli_fetch_assoc($result)) 
                {
                        echo "<tr><td>" . $row['idPopEtnie'] . "</td><td>" . $row['Etnie'] . "</td><td>" . $row['Populatie'] . "</td><td>" . $row['Anul'] . "</td><td>" . $row['Localitate'] . "</td></tr>";
                }
                        echo '</table>';
        }
?>
