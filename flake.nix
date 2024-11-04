{
  description = "TermiType 🚀: A terminal-based typing test application built with C++";

  inputs.nixpkgs.url = "github:nixos/nixpkgs";

  outputs = { self, nixpkgs }:
    let
      pkgs = import nixpkgs { system = "x86_64-linux"; };

      BIN_FILE_NAME = "ttype";
    in
    {
      defaultPackage.x86_64-linux = pkgs.stdenv.mkDerivation {
        pname = "ttype";
        version = "v1.0.0";

        src = ./.;

        buildInputs = [ pkgs.gcc pkgs.gnumake ];
        buildPhase = "make build";
        installPhase = ''
          mkdir -p $out/bin
          cp ${BIN_FILE_NAME} $out/bin/
        '';

        cleanPhase = "make clean";
      };

      devShell.x86_64-linux = pkgs.mkShell {
        buildInputs = [ pkgs.gcc pkgs.gnumake ];
      };
    };
}
