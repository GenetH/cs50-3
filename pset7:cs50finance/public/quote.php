<?php

    /**
     * quote.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Fanney Zhu
     * fanneyzhu@college.harvard.edu
     *
     * Find quote.
     */
    
    // requirements
    require("../includes/config.php");
    
    // if user submitted via POST
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check if symbol is empty
        if (empty($_POST["symbol"]))
        {
            apologize("Please provide a stock symbol.");
        }
        
        $stock = lookup($_POST["symbol"]);
        
        // check if symbol is valid
        if ($stock === false)
        {
            apologize("Invalid stock symbol.");
        }
        else
        {
            render("quote_display.php", ["title" => "Quote", 
            "price" => $stock["price"], "name" => $stock["name"],
            "symbol" => $stock["symbol"]]);
        }
    }
    
    else
    {
        render("quote_form.php", ["title" => "Quote"]);
    }
?>
