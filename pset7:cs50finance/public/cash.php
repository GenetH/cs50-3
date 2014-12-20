<?php
    
   /**
     * cash.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Fanney Zhu
     * fanneyzhu@college.harvard.edu
     *
     * Add cash.
     */
    
    // requirements
    require("../includes/config.php");    
    
    // if user submitted via POST
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check if symbol is empty
        if (empty($_POST["moreCash"]))
        {
            apologize("Please provide cash value.");
        }
        
        // check if cash value entered is valid
        if (!is_numeric($_POST["moreCash"]))
        {
            apologize("Invalid cash value.");
        }
        else
        {
            // update user's cash
            $before = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);        
            $update = number_format($before[0]["cash"] + $_POST["moreCash"], 4, ".", "");

            query("UPDATE users SET cash = ? WHERE id = ?", $update,
                  $_SESSION["id"]);

            // render cash_display.php       
            render("cash_display.php", ["title" => "Cash Display", 
            "moreCash" => $_POST["moreCash"], "cash" => $update]);
        }
    }
    else
    {
        render("cash_form.php", ["title" => "Cash Form"]);
    }

?>
