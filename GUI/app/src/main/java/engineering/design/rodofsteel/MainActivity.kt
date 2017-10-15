package engineering.design.rodofsteel

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.webkit.WebView
import android.widget.ImageButton
import android.widget.TextView
import io.github.controlwear.virtual.joystick.android.JoystickView
import android.R.attr.button
import android.content.DialogInterface
import android.support.v7.app.AlertDialog
import android.support.v7.widget.Toolbar
import android.util.Log
import android.view.Menu
import android.view.MenuItem
import android.view.View
import android.R.string.ok




class MainActivity : AppCompatActivity() {
    var gimbalIconShowing = true

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val myToolbar = findViewById<Toolbar>(R.id.my_toolbar)
        setSupportActionBar(myToolbar)

        // Initialize joystick
        val joystick = findViewById<JoystickView>(R.id.joystickView)

        // Message textview
        val msgTV = findViewById<TextView>(R.id.msgTV)

        // Webview setup
        val webView = findViewById<WebView>(R.id.webView)
        webView.loadUrl("https://tbnbooij.github.io/VideoStreamUnavailable/")

        // Left door buttons
        val lIn = findViewById<ImageButton>(R.id.leftIn)
        val lStop = findViewById<ImageButton>(R.id.leftStop)
        val lOut = findViewById<ImageButton>(R.id.leftOut)

        lIn.setOnClickListener {
            msgTV.setText(MsgGen.door(MsgGen.D_LEFT, MsgGen.D_IN))
        }

        lStop.setOnClickListener {
            msgTV.setText(MsgGen.door(MsgGen.D_LEFT, MsgGen.D_STOP))
        }

        lOut.setOnClickListener {
            msgTV.setText(MsgGen.door(MsgGen.D_LEFT, MsgGen.D_OUT))
        }

        // Right door buttons
        val rIn = findViewById<ImageButton>(R.id.rightIn)
        val rStop = findViewById<ImageButton>(R.id.rightStop)
        val rOut = findViewById<ImageButton>(R.id.rightOut)

        rIn.setOnClickListener {
            msgTV.setText(MsgGen.door(MsgGen.D_RIGHT, MsgGen.D_IN))
        }

        rStop.setOnClickListener {
            msgTV.setText(MsgGen.door(MsgGen.D_RIGHT, MsgGen.D_STOP))
        }

        rOut.setOnClickListener {
            msgTV.setText(MsgGen.door(MsgGen.D_RIGHT, MsgGen.D_OUT))
        }

        // Slope door buttons
        val sUp = findViewById<ImageButton>(R.id.slopeUp)
        val sStop = findViewById<ImageButton>(R.id.slopeStop)
        val sDown = findViewById<ImageButton>(R.id.slopeDown)

        sUp.setOnClickListener {
            msgTV.setText(MsgGen.slope(MsgGen.S_UP))
        }

        sStop.setOnClickListener {
            msgTV.setText(MsgGen.slope(MsgGen.S_STOP))
        }

        sDown.setOnClickListener {
            msgTV.setText(MsgGen.slope(MsgGen.S_DOWN))
        }

        // Gimbal/Wheel button
        val gwBtn = findViewById<ImageButton>(R.id.gwBtn)

        gwBtn.setOnClickListener {
            if (gimbalIconShowing)
            {
                gwBtn.setImageDrawable(getDrawable(R.drawable.car))
                joystick.setBackgroundColor(getResources().getColor(R.color.gimbalColor))
            }
            else
            {
                gwBtn.setImageDrawable(getDrawable(R.drawable.camera))
                joystick.setBackgroundColor(getResources().getColor(R.color.colorPrimaryDark))
            }
            gimbalIconShowing = !gimbalIconShowing
        }

        // Joystick view change listener
        joystick.setOnMoveListener { angle, strength ->

            // @TODO Do something with the speeds...
            if (gimbalIconShowing)
            {
                val v = (strength/100.0)*Math.sin(angle*2*Math.PI/360)
                val h = (strength/100.0)*Math.cos(angle*2*Math.PI/360)
                msgTV.setText(MsgGen.wheels(v, h))
            }
            else
            {
                if (strength == 0)
                {
                    msgTV.setText(MsgGen.gimbal(MsgGen.G_STOP))
                }
                else if (angle >= 315 || angle <= 45)
                {
                    msgTV.setText(MsgGen.gimbal(MsgGen.G_RIGHT))
                }
                else if (angle > 45 && angle < 135)
                {
                    msgTV.setText(MsgGen.gimbal(MsgGen.G_UP))
                }
                else if (angle >= 135 && angle <= 225)
                {
                    msgTV.setText(MsgGen.gimbal(MsgGen.G_LEFT))
                }
                else
                {
                    msgTV.setText(MsgGen.gimbal(MsgGen.G_DOWN))
                }

            }
        }

        // LED testing button
        val ledBtn = findViewById<ImageButton>(R.id.ledBtn)

        ledBtn.setOnClickListener {
            msgTV.setText(MsgGen.led())
        }


    }

    override fun onCreateOptionsMenu(menu: Menu): Boolean {
        // Inflate the menu; this adds items to the action bar if it is present.
        menuInflater.inflate(R.menu.barmenu, menu)
        return true
    }

    override fun onOptionsItemSelected(item: MenuItem): Boolean {
        when (item.getItemId()) {
            R.id.action_more -> {
                val builder = AlertDialog.Builder(this)
                builder.setMessage("Written by J.R van den Bemt and T.B.N. Booij for the course \"Engineering Design\" at the Eindhoven University of Technology.\n\nGroup members:\nBîrgăoanu, I., W.J.A. van Santvoort, T.B.N. Booij, J.R. van den Bemt, L.P.A. Verberk and O.C.A. Bolkenbaas\n")
                        .setTitle("About ROD of Steel")
                        .setNegativeButton("Dismiss", DialogInterface.OnClickListener { dialog, id ->

                        })
                        .create()
                        .show()


                return true
            }

            else ->
                // If we got here, the user's action was not recognized.
                // Invoke the superclass to handle it.
                return super.onOptionsItemSelected(item)
        }
    }
}
