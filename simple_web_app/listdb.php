<?php 

$MyUsername = "root";  
$MyPassword = "yourpasshere";  
$MyHostname = "localhost";      
$MyDBName = "M2M";
 

$conn = new mysqli($MyHostname, $MyUsername, $MyPassword, $MyDBName);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT * FROM phone";

$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "id: " . $row["id"]. " - DevId: " . $row["devid"]. " - Name: " . $row["name"]. " - Surname: " . $row["surname"]. " - Phone:" . $row["phone"]. "<br>";
    }
} else {
    echo "0 results";
}
$conn->close();

?>