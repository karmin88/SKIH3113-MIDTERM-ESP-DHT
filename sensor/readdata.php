<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "sensor_sql";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT date, time, temperature, humidity FROM sensordata ORDER BY id DESC";
$result = $conn->query($sql);

echo "<table border='1'>
<tr>
<th>Date</th>
<th>Time</th>
<th>Temperature (C)</th>
<th>Humidity (%)</th>
</tr>";

while($row = $result->fetch_assoc()) {
  echo "<tr>";
  echo "<td>" . $row['date'] . "</td>";
  echo "<td>" . $row['time'] . "</td>";
  echo "<td>" . $row['temperature'] . "</td>";
  echo "<td>" . $row['humidity'] . "</td>";
  echo "</tr>";
}
echo "</table>";

$conn->close();
?>
