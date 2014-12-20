<?php

   /**
     * register.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Fanney Zhu
     * fanneyzhu@college.harvard.edu
     *
     * Register user.
     */
     
    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php");
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // check if username is empty 
        if (empty($_POST["username"])) 
        {
            apologize("Please provide a username.");
        }
        
        // check if password is empty
        if (empty($_POST["password"]))
        {
            apologize("Please provide a password.");
        } 
        
        // check if password and confirmation is not the same
        if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match. Please try again.");
        }
        
        // insert new user into database
        $result = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", 
              $_POST["username"], crypt($_POST["password"]));
        
        // check if username already exists      
        if ($result === false)
        {
            apologize("Username already exists.");
        }
        
        // else find user's id
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        
        // store user's id in session
        $_SESSION["id"] = $rows[0]["id"];
        
        // redirect to index.php
        redirect("index.php");
    }

?>
