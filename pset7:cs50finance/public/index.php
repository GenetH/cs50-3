<?php

   /**
     * index.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Fanney Zhu
     * fanneyzhu@college.harvard.edu
     *
     * Controller.
     */
     
    // configuration
    require("../includes/config.php"); 

    // find user's cash
    $total = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $balance = $total[0]["cash"];
    
    // create array of associative arrays to store information
    $positions = [];
    $rows = query("SELECT symbol, shares FROM Portfolio WHERE id = ?", $_SESSION["id"]);
                  
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => number_format($stock["price"], 4, ".", ""),
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    
    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "positions" => $positions, "balance" => $balance]);
?>
