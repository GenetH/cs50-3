<?php

   /**
     * sell.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Fanney Zhu
     * fanneyzhu@college.harvard.edu
     *
     * Sell stocks.
     */

    // requirements
    require("../includes/config.php");
    
    // if user submitted via GET 
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // find shares of stock user owns
        $share = query("SELECT shares FROM Portfolio WHERE id = ? AND symbol = ?", 
                       $_SESSION["id"], $_POST["symbol"]); 
        if (empty($share))
        {
            apologize("You have no shares to sell.");
        }
        
        $numShares = $share[0]["shares"];
        
        // remove stock from portfolio
        query("DELETE FROM Portfolio WHERE id = ? AND symbol = ?", 
              $_SESSION["id"], $_POST["symbol"]);
        
        // update cash
        $stock = lookup($_POST["symbol"]);
        $update = number_format($stock["price"] * $numShares, 4, ".", "");
        query("UPDATE users SET cash = cash + ? WHERE id = ?", $update, 
              $_SESSION["id"]);     
        
        // update history database
        $datetime = date("m/d/y, g:i:s A");
        $symbolUpper = strtoupper($_POST["symbol"]);
        query("INSERT INTO History (id, transaction, datetime, symbol, shares, price)
              VALUES(?, ?, NOW(), ?, ?, ?)", $_SESSION["id"], "SELL", $symbolUpper, 
              $numShares, $update);
        
        // redirect to index.php
        redirect("index.php");
    }
    else
    {
        $symbols = query("SELECT symbol FROM Portfolio WHERE id = ?", 
        $_SESSION["id"]);
        
        // check if symbols exist
        if (empty($symbols))
        {
            apologize("You have no stocks to sell.");
        }
        
        // render sell_form.php
        render("sell_form.php", ["title" => "Sell", "symbols" => $symbols]);    
    }
    
?>
