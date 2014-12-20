<?php

    /**
     * search.php
     *
     * Computer Science 50
     * Problem Set 8
     *
     * Fanney Zhu
     * fanneyzhu@college.harvard.edu
     *
     * Search for places that matches user's input.
     */

    // requirement
    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // TODO: search database for places matching $_GET["geo"]
    $places = query("SELECT * FROM places WHERE MATCH(postal_code, place_name, admin_name1)
		     AGAINST (?) LIMIT 20", $_GET["geo"]);

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>
