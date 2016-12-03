<?php 

	 // Connect to MySQL
    include("dbconnect.php");
 
    $sql = "SELECT * FROM phone WHERE phone=".$_GET["phone"];

    //echo $sql;

	$result = $conn->query($sql);

	if ($result->num_rows > 0) {
	    // output data of each row
	    while($row = $result->fetch_assoc()) {
	        echo "true";
	    }
	} else {
	    echo "false";
	}
	$conn->close();


?>