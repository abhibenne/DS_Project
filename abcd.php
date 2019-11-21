<?php

sessions_start();
?>

<!DOCTYPE html>
<html>
<body>
	<?php
	$_SESSION['color']='green';
	echo "set";
	?>
</body>
</html>