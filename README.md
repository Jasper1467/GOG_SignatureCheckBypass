
# GOG_SignatureCheckBypass
This bypasses the GOG's (Good Old Games) signature checks.

## How it works
We force [WinVerifyTrust](https://learn.microsoft.com/en-us/windows/win32/api/wintrust/nf-wintrust-winverifytrust) to succeed, this way we don't directly have to patch GOG's own code, which they have more control over.
Reversed signature checking:

    // #STR: "getValidFileSignature failed closing WinVerifyTrust with e, "getValidFileSignature failed during WinVerifyTrust with er
    bool __stdcall getValidFileSignature(int a1)
    {
      // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]
    
      v10[1] = a1;
      pWVTData[6] = v10;
      v10[0] = 16;
      v10[2] = 0;
      v10[3] = 0;
      pgActionID.Data1 = 0xAAC56B;
      *&pgActionID.Data2 = 0x11D0CD44;
      *pgActionID.Data4 = 0xC000C28C;
      *&pgActionID.Data4[4] = 0xEE95C24F;
      v7 = 0;
      v9 = 0;
      pWVTData[0] = 52;
      pWVTData[1] = 0;
      pWVTData[2] = 0;
      pWVTData[3] = 2;
      pWVTData[4] = 0;
      pWVTData[5] = 1;
      v4 = 1;
      v5 = 0;
      v6 = 0;
      v8 = 0;
      nTrustStatus = WinVerifyTrust(0, &pgActionID, pWVTData);
      bTrust = nTrustStatus == 0;
      if ( nTrustStatus )
      {
        LastError = GetLastError();
        sub_4F0D10(
          "getValidFileSignature failed during WinVerifyTrust with error {} (detail code: {}).",
          83,
          &nTrustStatus,
          &LastError);
      }
      v4 = 2;
      nTrustStatus = WinVerifyTrust(0, &pgActionID, pWVTData);
      if ( nTrustStatus )
      {
        LastError = GetLastError();
        sub_4F0D10(
          "getValidFileSignature failed closing WinVerifyTrust with error {}, (detail code: {}).",
          85,
          &nTrustStatus,
          &LastError);
      }
      return bTrust;
    }

### Extra info
I found a function which lists all signatures that they allow, you can find them [here](https://github.com/Jasper1467/GOG_SignatureCheckBypass/blob/master/GOG_SignatureCheckBypass/Signatures.txt).
