package org.jessies.dalvikexplorer;

import android.app.*;
import android.content.*;
import android.os.*;
import android.text.ClipboardManager;
import android.text.*;
import android.text.style.*;
import android.view.*;
import android.widget.*;

/**
 * An abstract superclass for our TextView-based activities.
 */
public abstract class TextViewActivity extends Activity {
    private static final int CONTEXT_MENU_COPY = 0;
    private static final int CONTEXT_MENU_MAIL = 1;
    
    @Override public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        
        final TextView textView = (TextView) findViewById(R.id.output);
        registerForContextMenu(textView);
        
        final String extraValue = getExtraValue();
        textView.setText(content(extraValue), TextView.BufferType.SPANNABLE);
        setTitle(title(extraValue));
        
        final EditText searchView = (EditText) findViewById(R.id.search);
        searchView.addTextChangedListener(new TextWatcher() {
            public void afterTextChanged(Editable s) {
                setSearchString(s.toString());
            }
            public void beforeTextChanged(CharSequence s, int start, int count, int after) { }
            public void onTextChanged(CharSequence s, int start, int before, int count) { }
        });
    }
    
    @Override public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.options, menu);
        Compatibility.get().configureSearchView(this, menu);
        return true;
    }
    
    @Override public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
        case R.id.menu_search:
            if (Build.VERSION.SDK_INT < Build.VERSION_CODES.HONEYCOMB) {
                final EditText searchView = (EditText) findViewById(R.id.search);
                searchView.setVisibility(View.VISIBLE);
                searchView.requestFocus();
            }
            return true;
        default:
            return super.onOptionsItemSelected(item);
        }
    }
    
    protected String extraName() {
        return null;
    }
    
    protected abstract CharSequence title(String extraValue);
    
    protected abstract CharSequence content(String extraValue);
    
    protected String getExtraValue() {
        final String extraName = extraName();
        return (extraName != null) ? getIntent().getStringExtra(extraName) : null;
    }
    
    @Override public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
        super.onCreateContextMenu(menu, v, menuInfo);
        menu.setHeaderTitle("Details");
        menu.add(0, CONTEXT_MENU_COPY,  0, "Copy to clipboard"); // "Copy" might be ambiguous in FileViewerActivity.
        menu.add(0, CONTEXT_MENU_MAIL,  0, "Send as mail");
    }
    
    @Override public boolean onContextItemSelected(MenuItem item) {
        final TextView textView = (TextView) findViewById(R.id.output);
        final CharSequence title = getTitle();
        final CharSequence content = textView.getText();
        switch (item.getItemId()) {
        case CONTEXT_MENU_COPY:
            return copyToClipboard(title, content);
        case CONTEXT_MENU_MAIL:
            return mail(title, content);
        default:
            return super.onContextItemSelected(item);
        }
    }
    
    private boolean copyToClipboard(CharSequence title, CharSequence content) {
        final ClipboardManager clipboard = (ClipboardManager) getSystemService(CLIPBOARD_SERVICE);
        clipboard.setText(title + "\n\n" + content);
        return true;
    }
    
    private boolean mail(CharSequence title, CharSequence content) {
        final Intent intent = new Intent(Intent.ACTION_SEND);
        intent.setType("text/plain");
        intent.putExtra(Intent.EXTRA_SUBJECT, "Dalvik Explorer: " + title);
        intent.putExtra(Intent.EXTRA_TEXT, content);
        startActivity(intent);
        return true;
    }
    
    public void setSearchString(String needle) {
        clearSearch();
        if (needle.length() == 0) {
            return;
        }
        final TextView textView = (TextView) findViewById(R.id.output);
        Spannable spannable = (Spannable) textView.getText();
        String haystack = spannable.toString();
        for (int index = 0; index != -1; ) {
            index = haystack.indexOf(needle, index);
            if (index != -1) {
                spannable.setSpan(new BackgroundColorSpan(0xff337733), index, index + needle.length(), Spannable.SPAN_EXCLUSIVE_EXCLUSIVE);
                index += needle.length();
            }
        }
    }
    
    public void clearSearch() {
        final TextView textView = (TextView) findViewById(R.id.output);
        SpannableString spannable = (SpannableString) textView.getText();
        for (Object o : spannable.getSpans(0, spannable.length() - 1, BackgroundColorSpan.class)) {
            spannable.removeSpan(o);
        }
    }
}