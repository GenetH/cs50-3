<?php

   /**
     * buy.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Fanney Zhu
     * fanneyzhu@college.harvard.edu
     *
     * Buy shares of stock.
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
        
        // check if shares is empty
        if (empty($_POST["shares"]))
        {
            apologize("Please specify the number of shares you want to buy.");
        }
        
        // check if shares is valid
        if (!is_numeric($_POST["shares"]) || !preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Invalid number of shares.");
        }      
        
        $stock = lookup($_POST["symbol"]);
        
        // check if symbol is valid
        if ($stock === false)
        {
            apologize("Invalid stock symbol.");
        }
        
        // check if user has enough cash
        $total = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $balance = $total[0]["cash"];
        $update = number_format($stock["price"] * $_POST["shares"], 4, ".", "");
        if ($update > $balance)
        {
            apologize("Not enough cash.");
        }
        
        // store stock symbol in Portfolio
        $symbolUpper = strtoupper($_POST["symbol"]);
        
        $result = query("INSERT INTO Portfolio (id, symbol, shares) VALUES(?, ?, ?) 
                        ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", 
                        $_SESSION["id"], $symbolUpper, $_POST["shares"]);
        
        // update user's cash 
        query("UPDATE users SET cash = cash - ? WHERE id = ?", $update, $_SESSION["id"]);
        
        // update history database
        query("INSERT INTO History (id, transaction, datetime, symbol, shares, price)
              VALUES(?, ?, NOW(), ?, ?, ?)", $_SESSION["id"], "BUY", $symbolUpper, 
              $_POST["shares"], $update);
        
        // redirect
        redirect("index.php");
    }
    else
    {
        render("buy_form.php", ["title" => "Buy"]);
    }
?>
