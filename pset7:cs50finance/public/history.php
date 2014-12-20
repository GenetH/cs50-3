<?php

   /**
     * history.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Fanney Zhu
     * fanneyzhu@college.harvard.edu
     *
     * History of all transactions.
     */

    // requirements
    require("../includes/config.php");
    
    // create array of associative arrays to store information
    $positions = [];
    $rows = query("SELECT * FROM History WHERE id = ?", $_SESSION["id"]);
    
    // check if rows exist
    if (empty($rows))
    {
        apologize("No transactions have been made.");
    }              
    else
    {
        foreach ($rows as $row)
        {
            $positions[] = [
                "transaction" => $row["transaction"],
                "datetime" => $row["datetime"],
                "symbol" => $row["symbol"],
                "shares" => $row["shares"],
                "price" => $row["price"]
            ];
        }
        
        // render history_form.php
        render("history_form.php", ["title" => "History", "positions" => $positions]);
    }
?>
