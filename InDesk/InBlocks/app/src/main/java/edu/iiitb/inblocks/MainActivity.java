package edu.iiitb.inblocks;

import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;


public class MainActivity extends ActionBarActivity {

    private final String TAG = MainActivity.class.getSimpleName();
    private boolean isVirtual = true;

    public static final String EXTRA_DEVICE_ADDRESS = "device_address";

    // Local Bluetooth adapter
    private BluetoothAdapter mBluetoothAdapter = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button realButton = (Button) findViewById(R.id.real);
        Button virtualButton = (Button) findViewById(R.id.virtual);

        // Check if bluetooth is available
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (mBluetoothAdapter == null   )
        {
            Toast.makeText(this, "Bluetooth is not available. Can't use Real Robot", Toast.LENGTH_SHORT)
                    .show();
            realButton.setClickable(false);
        } else {
            realButton.setClickable(true);
        }

        realButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View view)
            {
                isVirtual = false;
                Intent blocksActivityIntent = new Intent(MainActivity.this, BlocksActivity.class);
//                blocksActivityIntent.putExtra(EXTRA_DEVICE_ADDRESS, "00:13:EF:01:11:3D");
                blocksActivityIntent.putExtra(EXTRA_DEVICE_ADDRESS, "00:12:10:23:22:12");
                startActivity(blocksActivityIntent);
            }
        });

        virtualButton.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View view)
            {
                isVirtual = true;
                Intent blocksActivityIntent = new Intent(MainActivity.this, BlocksActivity.class);
                startActivity(blocksActivityIntent);
            }

        });
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.d(TAG, "Is Virtual? " + isVirtual);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }
}
