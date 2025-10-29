import eslint from "@eslint/js";
import tseslint from "typescript-eslint";
import prettier from "eslint-plugin-prettier";

export default tseslint.config(
  eslint.configs.recommended,
  tseslint.configs.recommended,
  {
    // files: ["**/*.ts",],
    plugins: {
      prettier,
    },
    languageOptions: {
      globals: {
        console: "readonly", // allow console without "no-undef"
        process: "readonly", // allow console without "no-undef"
      },
    },
    rules: {
      "@typescript-eslint/no-unused-vars": "error",
      "@typescript-eslint/no-explicit-any": "error",
      // "no-unused-vars": "warn",
      // "no-undef": "warn",
      semi: ["error", "never"],
      "prefer-const": "error",
      "prettier/prettier": "warn",
      "eol-last": ["error", "always"],
    },
  },
);
