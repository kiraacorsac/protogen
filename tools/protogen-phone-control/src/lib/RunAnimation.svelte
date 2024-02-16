<script lang="ts">
  import ProtogenConfirmationButton from "./ProtogenConfirmationButton.svelte";

  export let name;
  export let url;
</script>

<ProtogenConfirmationButton path="animation" title={name} {url} value={name} />

<style>
</style>
