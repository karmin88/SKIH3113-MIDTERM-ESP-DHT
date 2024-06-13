<?php
$servername = "localhost";
$username = "root"; // Replace with your MySQL username
$password = ""; // Replace with your MySQL password
$dbname = "sensor_sql"; // Replace with your database name

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Check if 'temperature' and 'humidity' are set in the POST request
if (isset($_POST['temperature']) && isset($_POST['humidity'])) {
    $temperature = $_POST['temperature'];
    $humidity = $_POST['humidity'];

    // Insert data into database
    $sql = "INSERT INTO sensordata (date, time, temperature, humidity)
            VALUES (CURDATE(), CURTIME(), '$temperature', '$humidity')";

    if ($conn->query($sql) === TRUE) {
        echo "New record created successfully";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
} else {
    echo "Temperature and humidity data not received.";
}

$conn->close();
?>