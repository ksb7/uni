<?php
        include_once '../conect.php';

        $sql = "select * from localitate;";
        $result = mysqli_query($conn, $sql);
        $resultCheck = mysqli_num_rows($result);


        if ($resultCheck > 0) 
        {
                while ($row = mysqli_fetch_assoc($result)) 
                {
                        echo "<tr><td>" . $row['idLocalitate'] . "</td><td>" . $row['Localitate'] . "</td></tr>";
                }
                        echo '</table>';
        }
?>
